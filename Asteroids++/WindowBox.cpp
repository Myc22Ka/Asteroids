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
#include "DeathScreen.h"

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
	DeathScreen deathScreen;

    initSprite(background, "background", backgroundTexture);
	initSprite(loader, "loader", loaderTexture);

    Clock clock;
    
    GameOver::init();
    Menu::init();
    Game::setGameState(MENU_LOADING);
	launch.startEffect(5.0f);

    loadParticles();

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
        deathScreen.init(deltaTime, window);

        window.display();
    }
}

void WindowBox::engine(Wind& wind, const float& deltaTime)
{
    if (Game::getGameState() == MENU_LOADING) {
		//launchGame(deltaTime);
		Game::setGameState(MENU);
		return;
    }

    if (Game::getGameState() == MENU) {
        displayMenu();
		Menu::update(deltaTime);
        return;
    }

    updateWindow(deltaTime);

	wind.init(deltaTime, window);
    Game::spawnEnemy(deltaTime);

    renderUI();

    if (Game::getGameState() == GAME_OVER) {
        Game::clearEntities();
        window.draw(GameOver::gameOverText.getText());
        window.draw(GameOver::continueText.getText());

        if (Keyboard::isKeyPressed(Keyboard::Enter)) begin();
    }
}

void WindowBox::launchGame(const float& deltaTime) {
	Color color = loader.getColor();

	if (launch.isEffectActive() && loaderSprite.spriteState != loaderSprite.frames.size() - 1) {
        launch.updateEffectDuration(deltaTime);
	    float opacity = 255.0f * (1 - launch.getEffectDuration() / 5.0f);

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

		color.a = static_cast<Uint8>(opacity);

		loader.setColor(color);
		loaderSprite.sprite.setColor(color);

        if (!launch.isEffectActive() && loaderSprite.spriteState == loaderSprite.frames.size() - 1) Game::setGameState(MENU);
	}

    window.draw(loader);
	window.draw(loaderSprite.sprite, Transform().translate(Vector2f(600.0f, 450.0f)).scale(10.0f, 10.0f));

    for (auto& [circle, velocity] : loaderParticles) {
		velocity.x += sin(circle.getPosition().y / 0.5f);

	    circle.move(velocity);

        Color c = circle.getFillColor();
		c.a = min(color.a, static_cast<Uint8>(150.0f));

        circle.setFillColor(c);

	    FloatRect bounds(-circle.getRadius(), -circle.getRadius(), window.getSize().x + circle.getRadius(), window.getSize().y + circle.getRadius());

	    if (!bounds.contains(circle.getPosition())) {
		    if (circle.getPosition().x < bounds.left)
			    circle.setPosition(bounds.left + bounds.width, circle.getPosition().y);
		    else if (circle.getPosition().x > bounds.left + bounds.width)
			    circle.setPosition(bounds.left, circle.getPosition().y);
		    if (circle.getPosition().y < bounds.top)
			    circle.setPosition(circle.getPosition().x, bounds.top + bounds.height);
		    else if (circle.getPosition().y > bounds.top + bounds.height)
			    circle.setPosition(circle.getPosition().x, bounds.top);
	    }

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

        if (Game::freeze.isEffectActive() || Game::getGameState() == PAUSED)
			continue;
        particle->update(deltaTime);
    }

    for (auto& entity : Game::getEntities())
    {
		if (!entity || !entity->isActive() || (DeathScreen::isScreenOver() && entity->getEntityType() == TYPE_PLAYER))
			continue;
        entity->render(window);

        if ((Game::freeze.isEffectActive() && Game::isEntityInsideGroup(entity, FREEZE_GROUP)) || (Game::getGameState() == PAUSED && entity->getEntityType() != TYPE_EXPLOSION))
			continue;
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

void WindowBox::loadParticles() {
	for (size_t i = 0; i < 50; i++) {
		CircleShape circle(physics::getRandomFloatValue(10.0f, 1.5f));
		circle.setPosition(physics::getRandomPosition(circle.getRadius()));
		circle.setFillColor(Color(208, 241, 255, 150));
		const auto velocity = Vector2f(physics::getRandomFloatValue(2.5f), physics::getRandomFloatValue(physics::getPI() / 2, 0.2f));
		loaderParticles.push_back({ circle, velocity });
	}
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