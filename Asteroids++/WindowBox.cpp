#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include "Score.h"
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

    //vector<Page*> pages {new MenuLoader()};

    Wind wind;
	DeathScreen deathScreen;
    MenuLoader loader;
    HighScoreTable highScoreTable;
    GameOver gameOver;
    Menu menu;

    if (!backgroundTexture.loadFromFile("./assets/background.png")) cout << "Error: Cannot load background!" << endl;

    background.setTexture(backgroundTexture);

    Clock clock;
    

    loader.init();


    fps.setSize(FileMenager::screenData.fps_font_size);

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
            menu.navigator(e);
            break;
        case MENU_HIGHSCORE:
            menu.navigator(e);
            break;
        case GAME_OVER:
            gameOver.enterPlayerName(e);
            break;
        default:
            break;
        }

        engine(wind, loader, gameOver, highScoreTable, menu, deltaTime);
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
    case Keyboard::Num9:
        wind.forceWind(10.0f, 4.0f, physics::getRandomDirection());
        break;
    case Keyboard::Num0:
        Game::freeze.startEffect(physics::getRandomFloatValue(5.0f, 0.5f) + Player::playerStats.time);
        Game::setGameState(FREZZE);
        break;
    case Keyboard::P:
        Game::setGameState(PAUSED);
        break;
    }
}

void WindowBox::engine(Wind& wind, MenuLoader& loader, GameOver& gameOver, HighScoreTable& highScoreTable, Menu& menu, const float& deltaTime)
{
    switch (Game::getGameState())
    {
    case MENU_LOADING:
        loader.run(deltaTime, window);
        //Game::setGameState(MENU);
        return;
    case MENU:
        menu.run(deltaTime, window);
        return;
    case MENU_HIGHSCORE:
        highScoreTable.run(deltaTime, window);
        return;
    case GAME_OVER:
        Game::clearEntities();
        Game::clearParticles();
        wind.remove();
        gameOver.run(deltaTime, window);
        Game::level = 1;

        return;
    }

    updateWindow(deltaTime);

    wind.init(deltaTime, window);
    Game::spawnEnemy(deltaTime);

    renderUI();
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

    if (!Game::freeze.isEffectActive() && Game::getGameState() == FREZZE) Game::setGameState(PLAYING);
    if (SoundData::sounds[Sounds::AMBIENT].getStatus() == Sound::Paused && Game::getGameState() == PLAYING) SoundData::renev(Sounds::AMBIENT);

    for (auto& entity : Game::getEntities())
    {
        if (!entity || !entity->isActive() || (DeathScreen::isScreenOver() && entity->getEntityType() == TYPE_PLAYER)) continue;

        entity->render(window);

        if (Game::getGameState() == DEATH && entity->getEntityType() != TYPE_EXPLOSION && entity->getEntityType() != TYPE_ENEMY_BULLET && entity->getEntityType() != TYPE_BULLET_SINGLE) continue;

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