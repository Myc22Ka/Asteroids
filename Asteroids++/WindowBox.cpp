#include "Player.h"
#include "Asteroid.h"
#include <iostream>
#include "Score.h"
#include "GameOver.h"
#include "Menu.h"
#include "Physics.h"
#include "DashBar.h"
#include "WindowBox.h"
#include "PlayerHealthUI.h"
#include "SingleAsteroid.h"
#include "Wind.h"

vector<PlayerHealthUI> WindowBox::playerHealthUIs;
VideoMode WindowBox::videoMode{};

WindowBox::WindowBox() {}

VideoMode WindowBox::getVideoMode() {
	return videoMode;
}

void WindowBox::displayWindow() {
	videoMode = VideoMode(1200, 900);
	//videoMode = VideoMode::getDesktopMode();

    window.create(videoMode, "Asteroids++", Style::None);
    window.setFramerateLimit(60);

    loaderSprite = getSprite(Sprites::PICKUP_DRUNKMODE);

    Wind wind;

    initSprite(background, "background", backgroundTexture);
	initSprite(loader, "loader", loaderTexture);

    Clock clock;
    
    GameOver::init();
    Menu::init();
    Game::setGameState(MENU_LOADING);
	launch.startEffect(5.0f);

    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disPos(0.0f, 800.0f);

    for (size_t i = 0; i < 100; i++) {
		CircleShape circle(physics::getRandomFloatValue(5.0f));
		circle.setPosition(disPos(gen), disPos(gen));
		circle.setFillColor(sf::Color(255, 255, 255, 150));
		loaderParticles.push_back(circle);
    }

    while (window.isOpen()) {
        Event e{};

        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed || e.key.code == sf::Keyboard::Escape) window.close();

            if (Game::getGameState() == MENU) Menu::navigator(e);

            else if (e.type == sf::Event::KeyPressed) {

                if (e.key.code == sf::Keyboard::H) {
                    Game::hitboxesVisibility = !Game::hitboxesVisibility;
                    float lastTime = 0;

                    float currentTime = clock.restart().asSeconds();
                    float fps = 1.0f / (currentTime - lastTime);
                    lastTime = currentTime;

                    cout << fps << endl;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();

        engine(wind, deltaTime);

        window.display();
    }
}

void WindowBox::engine(Wind& wind, const float& deltaTime)
{
    if (Game::getGameState() == MENU_LOADING) {
		launchGame(deltaTime);
		//Game::setGameState(MENU);
		return;
    }

    if (Game::getGameState() == MENU) {
        displayMenu();
		Menu::update(deltaTime);
        return;
    }

    updateWindow(deltaTime);
    updateWind(wind, deltaTime);
    spawnEnemy(deltaTime);
    renderUI();

    if (Game::getGameState() == GAME_OVER) {
        Game::clearEntities();
        window.draw(GameOver::gameOverText.getText());
        window.draw(GameOver::continueText.getText());

        if (Keyboard::isKeyPressed(Keyboard::Enter)) begin();
    }
}

void WindowBox::launchGame(const float& deltaTime) {
	if (launch.isEffectActive() && loaderSprite.spriteState != loaderSprite.frames.size() - 1) {
        launch.updateEffectDuration(deltaTime);
	    float opacity = 255.0f * (1 - launch.getEffectDuration() / 5.0f);

        Color color = loader.getColor();
	    color.a = static_cast<Uint8>(opacity);

		loader.setColor(color);
		loaderSprite.sprite.setColor(color);
    }

    if (!launch.isEffectActive()) {
		loaderSprite.currentSpriteLifeTime -= deltaTime;

        if (loaderSprite.spriteState == loaderSprite.frames.size() - 1)
			launch.startEffect(5.0f);

		if (loaderSprite.currentSpriteLifeTime <= 0) {
			loaderSprite.currentSpriteLifeTime = loaderSprite.defaultSpriteLifeTime;
			loaderSprite.spriteState = (loaderSprite.spriteState + 1) % loaderSprite.frames.size();
			updateSprite(loaderSprite.sprite, loaderSprite.frames, loaderSprite.spriteState);
		}
    };

    if (launch.isEffectActive() && loaderSprite.spriteState == loaderSprite.frames.size() - 1) {
		launch.updateEffectDuration(deltaTime);
		float opacity = 255.0f * (launch.getEffectDuration() / 5.0f);

		Color color = loader.getColor();
		color.a = static_cast<Uint8>(opacity);

		loader.setColor(color);
		loaderSprite.sprite.setColor(color);

        if (!launch.isEffectActive() && loaderSprite.spriteState == loaderSprite.frames.size() - 1) {
		    Game::setGameState(MENU);
        }
	}

    window.draw(loader);
	window.draw(loaderSprite.sprite, Transform().translate(Vector2f(600.0f, 450.0f)).scale(10.0f, 10.0f));

    for (auto& circle : loaderParticles) {
		circle.move(physics::getRandomDirection());
		window.draw(circle);
	}
}

void WindowBox::initSprite(Sprite& sprite, const string filename, Texture& texture) {
	if (!texture.loadFromFile("./assets/" + filename + ".png")) cout << "Error: Cannot load background!" << endl;

    sprite.setTexture(texture);

    //sprite.setScale(
	//	static_cast<float>(FileMenager::screenData.size_width) / texture.getSize().x,
	//	static_cast<float>(FileMenager::screenData.size_height) / texture.getSize().y);
}

void WindowBox::displayMenu() {
    if (Game::getGameState() == MENU) {
		Menu::draw(window);

        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			const auto option = Menu::getSelectedOptionIndex();

           switch (option) {
			case 0:
			    begin();
			    break;
			case 1:
			    cout << "Continue!\n"; 
                break;
			case 2:
				cout << "HighScore!\n";
                break;
			case 3:
				SoundData::play(Sounds::GOODBYE);
				this_thread::sleep_for(chrono::milliseconds(1000));

				window.close();
				break;
		    }
        }
        return;
    }
}

void WindowBox::updateWindow(const float& deltaTime)
{
    window.draw(background);

    for (auto& particle : Game::getParticles())
    {
        if (!particle->isActive()) continue;
        particle->render(window);

        if (Game::freeze.isEffectActive()) continue;
        particle->update(deltaTime);
    }

    for (auto& entity : Game::getEntities())
    {
        if (!entity || !entity->isActive()) continue;
        entity->render(window);

        if (Game::freeze.isEffectActive() && Game::isEntityInsideGroup(entity, FREEZE_GROUP)) continue;
        entity->update(deltaTime);
    }


    for (size_t i = 0; i < playerHealthUIs.size(); ++i) {
        playerHealthUIs[i].update(deltaTime);
        playerHealthUIs[i].draw(window);
    }
}

void WindowBox::renderUI()
{
    Score::scoreText.setText(Score::getScoreString());
    window.draw(Score::scoreText.getText());

    DashBar dashBar;

    dashBar.update(min(1 - Player::dashTimer / FileMenager::playerData.dash_time_delay, 1.0f));
    dashBar.draw(window);
}

void WindowBox::updateWind(Wind& wind, const float& deltaTime)
{
    wind.activateWind(physics::getRandomFloatValue(10.0f, 0.75f) + Player::playerStats.time, physics::getRandomFloatValue(3.0f), physics::getRandomDirection());

    wind.update(deltaTime);

    if (Game::freeze.isEffectActive())
    {
        Game::freeze.updateEffectDuration(deltaTime);
        wind.stopWind();
    }

    wind.render(window);
}

void WindowBox::begin()
{
    Game::setGameState(PLAYING);
    Game::addEntity(new Player());
    Game::enemySpawn.setEffectDuration(FileMenager::timingsData.default_enemy_spawn_time);
    playerHealthUIs.clear();

    Score::init();

    float offset = 0.0f;

    for (int i = 0; i < Player::playerStats.lifes; ++i) {
        playerHealthUIs.push_back(offset);

        offset += 20.0f;
    }
}

void WindowBox::spawnEnemy(const float& deltaTime)
{
    Game::enemySpawn.updateEffectDuration(deltaTime);

    if (Game::enemySpawn.getEffectDuration() <= 0 && !Game::freeze.isEffectActive()) {
        Game::addEntity(Game::getRandomEntity());
		Game::enemySpawn.setEffectDuration(FileMenager::timingsData.default_enemy_spawn_time + Player::playerStats.time * 0.1f);
    }
}