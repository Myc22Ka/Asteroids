#include "Player.h"
#include "Asteroid.h"
#include <iostream>
#include "Score.h"
#include "Physics.h"
#include "DashBar.h"
#include "HealthBar.h"
#include "WindowBox.h"
#include "PlayerHealthUI.h"
#include "SingleAsteroid.h"
#include "Wind.h"

double WindowBox::asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
vector<PlayerHealthUI> WindowBox::playerHealthUIs;

WindowBox::WindowBox() {}

void WindowBox::displayWindow()
{
    window.create(VideoMode(FileMenager::screenData.size_width, FileMenager::screenData.size_height), "Asteroids++", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);

    Wind wind;

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./assets/background.png")) {
        cout << "Error: Cannot load background!" << endl;
    }

    Sprite backgroundSprite(backgroundTexture);

    Vector2u windowSize = window.getSize();

    backgroundSprite.setScale(static_cast<float>(windowSize.x) / backgroundTexture.getSize().x, static_cast<float>(windowSize.y) / backgroundTexture.getSize().y);

    Clock clock;
    init();
    begin();

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            else if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Q) {
                    std::cout << Game::getParticles().size() << std::endl;
                }
                if (e.key.code == sf::Keyboard::H) {
                    Game::hitboxesVisibility = !Game::hitboxesVisibility;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        wind.activateWind(physics::getRandomFloatValue(10.0f, 0.75f), physics::getRandomFloatValue(3.0f), physics::getRandomDirection());

        wind.update(deltaTime);

        if (Game::freeze.isEffectActive()) 
        { 
            Game::freeze.updateEffectDuration(deltaTime); 
            wind.stopWind();
        }

        window.clear();
        window.draw(backgroundSprite);
        wind.render(window);

        asteroidSpawnTime -= deltaTime;

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

        Score::scoreText.setString(std::to_string(Score::score));
        window.draw(Score::scoreText);

        DashBar dashBar;

        dashBar.update(min(1 - Player::dashTimer / FileMenager::playerData.dash_time_delay, 1.0));
        dashBar.draw(window);

        for (size_t i = 0; i < playerHealthUIs.size(); ++i) {
            playerHealthUIs[i].update(deltaTime);
            playerHealthUIs[i].draw(window);
        }

        spawnEnemy();

        if (Game::isGameOver) {
            Game::clearEntities();
            Score::score = 0;
            begin();
        }

        window.display();

    }
}
void WindowBox::begin()
{
    Game::isGameOver = false;
    Game::addEntity(new Player());
    asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
    playerHealthUIs.clear();

    double offset = 0;

    for (int i = 0; i < Player::playerStats.lifes; ++i) {
        playerHealthUIs.push_back(offset);

        offset += 20.0f;
    }
}

void WindowBox::spawnEnemy()
{
    if (asteroidSpawnTime <= 0 && !Game::freeze.isEffectActive()) {
        Game::addEntity(Game::getRandomEntity());
        asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
    }
}

void WindowBox::init()
{
    Score::init();
}