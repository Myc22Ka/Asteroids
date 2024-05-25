#include "Player.h"
#include "Enemy.h"
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

VideoMode WindowBox::videoMode{};
TextField WindowBox::fps{ 0 };

WindowBox::WindowBox() {}

VideoMode WindowBox::getVideoMode() {
	return videoMode;
}

void WindowBox::displayWindow() {
	videoMode = VideoMode(1500, 1080);
    //videoMode = VideoMode::getDesktopMode();

    window.create(videoMode, "Asteroids++", Style::None);
    window.setFramerateLimit(FileMenager::screenData.framerate);

    loaderSprite = getSprite(Sprites::LOADER);

    Wind wind;
	DeathScreen deathScreen;

    initSprite(background, "background", backgroundTexture);
	initSprite(loader, "loader", loaderTexture);

    Clock clock;
    
    GameOver::init();
    Menu::init();
    Game::setGameState(MENU_LOADING);
    launch.startEffect(FileMenager::screenData.launch_time);
    fps.setSize(FileMenager::screenData.fps_font_size);

    loadParticles();

    while (window.isOpen()) {
        Event e{};

        while (window.pollEvent(e)) {
            switch (e.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                handleKeyPress(e.key.code, wind);
                break;
            default:
                break;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();

        switch (Game::getGameState()) {
        case MENU:
            Menu::navigator(e);
            break;
        case MENU_HIGHSCORE:
            Menu::navigator(e);
            break;
        case GAME_OVER:
            GameOver::enterPlayerName(e);
            break;
        default:
            break;
        }

        engine(wind, deltaTime); 
        deathScreen.init(deltaTime, window);

        window.display();
    }
}

void WindowBox::handleKeyPress(Keyboard::Key keyCode, Wind& wind) {
    switch (keyCode) {
    case Keyboard::Escape:
        window.close();
        break;
    case Keyboard::H:
        Game::hitboxesVisibility = !Game::hitboxesVisibility;
        break;
    case Keyboard::P:
        wind.forceWind(10.0f, 4.0f, physics::getRandomDirection());
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

    if (Game::getGameState() == MENU_HIGHSCORE) {
        Menu::displayHighscoreTable(window);
        Menu::update(deltaTime);
        return;
    }

    if (Game::getGameState() == GAME_OVER) {
        Game::clearEntities();
        Game::clearParticles();
        wind.remove();
        GameOver::draw(window);
        GameOver::drawPlayerName(window);

        GameOver::update(deltaTime);

        return;
    }

    updateWindow(deltaTime);

	wind.init(deltaTime, window);
    Game::spawnEnemy(deltaTime);

    renderUI();
}

void WindowBox::launchGame(const float& deltaTime) {
	Color color = loader.getColor();

	if (launch.isEffectActive() && loaderSprite.spriteState != loaderSprite.frames.size() - 1) {
        launch.updateEffectDuration(deltaTime);
	    float opacity = 255.0f * (1 - launch.getEffectDuration() / FileMenager::screenData.launch_time);

	    color.a = static_cast<Uint8>(opacity);

		loader.setColor(color);
		loaderSprite.sprite.setColor(color);
    }

    if (!launch.isEffectActive()) {
		loaderSprite.currentSpriteLifeTime -= deltaTime;

        if (loaderSprite.spriteState == loaderSprite.frames.size() - 1)
			launch.startEffect(FileMenager::screenData.launch_time);

		if (loaderSprite.currentSpriteLifeTime <= 0) {
			loaderSprite.currentSpriteLifeTime = loaderSprite.defaultSpriteLifeTime;
			loaderSprite.spriteState = (loaderSprite.spriteState + 1) % loaderSprite.frames.size();
			updateSprite(loaderSprite.sprite, loaderSprite.frames, loaderSprite.spriteState);
		}
    };

    if (launch.isEffectActive() && loaderSprite.spriteState == loaderSprite.frames.size() - 1) {
		launch.updateEffectDuration(deltaTime);
		float opacity = 255.0f * (launch.getEffectDuration() / FileMenager::screenData.launch_time);

		color.a = static_cast<Uint8>(opacity);

		loader.setColor(color);
		loaderSprite.sprite.setColor(color);

        if (!launch.isEffectActive() && loaderSprite.spriteState == loaderSprite.frames.size() - 1) Game::setGameState(MENU);
	}

    window.draw(loader);
	window.draw(loaderSprite.sprite, Transform().translate(Vector2f(videoMode.width >> 1, videoMode.height >> 1)));

    for (auto& [circle, velocity] : loaderParticles) {
		velocity.x += sin(circle.getPosition().y / 0.5f);

	    circle.move(velocity);

        Color c = circle.getFillColor();
		c.a = min(color.a, static_cast<Uint8>(FileMenager::screenData.launch_particle_opacity));

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
}

void WindowBox::displayMenu() {
    if (Game::getGameState() != MENU) return;

    Menu::draw(window);

    
}

void WindowBox::updateWindow(const float& deltaTime)
{
    window.draw(background);

    for (auto& particle : Game::getParticles())
    {
        if (!particle->isActive()) continue;
            particle->render(window);
            particle->update(deltaTime);
    }

    if (!Game::freeze.isEffectActive() && SoundData::sounds[Sounds::AMBIENT].getStatus() == Sound::Paused && Game::getGameState() == PLAYING) SoundData::renev(Sounds::AMBIENT);

    for (auto& entity : Game::getEntities())
    {
        if (!entity || !entity->isActive() || (DeathScreen::isScreenOver() && entity->getEntityType() == TYPE_PLAYER))
            continue;

        entity->render(window);

        if ((Game::freeze.isEffectActive() && entity->getEntityType() == TYPE_EVENT_WIND) || (Game::getGameState() == PAUSED && entity->getEntityType() != TYPE_EXPLOSION && entity->getEntityType() != TYPE_ENEMY_BULLET && entity->getEntityType() != TYPE_BULLET_SINGLE))
            continue;

        entity->update(deltaTime);
    }


    for (auto& life : Player::playerStats.lifes) {
        life.update(deltaTime);
        life.draw(window);
    }

    fpsDelay.updateEffectDuration(deltaTime);

    if (!fpsDelay.isEffectActive()) {
        fpsDelay.startEffect(0.2f);
        float lastTime = 0;
        fps.setText(to_string(static_cast<int>(1.0f / (deltaTime - lastTime))) + " FPS");
        fps.setTextPosition(Vector2f(FileMenager::screenData.fps_pos_x + FileMenager::screenData.padding, FileMenager::screenData.fps_pos_y + FileMenager::screenData.padding));
        lastTime = deltaTime;
    }

    window.draw(fps.getText());
}

void WindowBox::renderUI()
{
    Score::scoreText.setText(Score::getScoreString());
    window.draw(Score::scoreText.getText());

    if (Score::getScore() / FileMenager::screenData.game_next_level_spike > Game::level && Game::level != Game::maxLevel) Game::level += 1;

    DashBar dashBar;

    dashBar.update(min(1 - Player::dash.getEffectDuration() / FileMenager::playerData.dash_time_delay, 1.0f));
    dashBar.draw(window);
}

void WindowBox::loadParticles() {
	for (size_t i = 0; i < 50; i++) {
		CircleShape circle(physics::getRandomFloatValue(10.0f, 1.5f));
		circle.setPosition(physics::getRandomPosition(circle.getRadius()));
		circle.setFillColor(Color(208, 241, 255, FileMenager::screenData.launch_particle_opacity));
		const auto velocity = Vector2f(physics::getRandomFloatValue(2.5f), physics::getRandomFloatValue(physics::getPI() / 2, 0.2f));
		loaderParticles.push_back({ circle, velocity });
	}
}

void WindowBox::begin()
{
    Game::setGameState(PLAYING);
    SoundData::sounds[Sounds::AMBIENT].setVolume(100);
    SoundData::playLooped(Sounds::AMBIENT);

    Game::addEntity(new Player());
    Game::enemySpawn.setEffectDuration(FileMenager::timingsData.default_enemy_spawn_time);
    fps.setColorText(Color(255, 255, 255, 150));

    Score::init();
}