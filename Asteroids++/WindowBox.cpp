module;

#include "Player.h"
#include "Asteroid.h"
#include <iostream>
#include "Score.h"
#include "Physics.h"
#include "DashBar.h"
#include "HealthBar.h"

module WindowBox;

double WindowBox::asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;

WindowBox::WindowBox() {}

void WindowBox::displayWindow()
{
    window.create(VideoMode(FileMenager::screenData.size_width, FileMenager::screenData.size_height), "Asteroids++", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./assets/background.png")) {
        cout << "Error: Cannot load background!" << endl;
    }

    Sprite backgroundSprite(backgroundTexture);

    sf::Vector2u windowSize = window.getSize();

    backgroundSprite.setScale(windowSize.x / (double)backgroundTexture.getSize().x, windowSize.y / (double)backgroundTexture.getSize().y);

    Clock clock;
    init();
    begin();

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            else if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Q) {
                    std::cout << Game::entities.size() << std::endl;
                }
                if (e.key.code == sf::Keyboard::H) {
                    Game::hitboxesVisibility = !Game::hitboxesVisibility;
                }
            }
        }

        double deltaTime = clock.restart().asSeconds();

        Game::toAddList.clear();
        Game::toRemoveList.clear();

        window.clear();
        window.draw(backgroundSprite);

        asteroidSpawnTime -= deltaTime;

        for (size_t i = 0; i < Game::entities.size(); i++)
        {
            Game::entities[i]->update(deltaTime);
            Game::entities[i]->render(window);
        }

        std::vector<Entity*> entitiesToAdd;
        std::vector<Entity*> entitiesToRemove;

        for (auto& ptr : Game::toAddList) {
            entitiesToAdd.push_back(ptr);
        }
        Game::toAddList.clear();

        for (auto& ptr : Game::toRemoveList) {
            entitiesToRemove.push_back(*ptr);
        }
        Game::toRemoveList.clear();

        for (auto ptr : entitiesToAdd) {
            Game::entities.push_back(ptr);
        }

        for (auto ptr : entitiesToRemove) {
            auto it = std::find(Game::entities.begin(), Game::entities.end(), ptr);
            if (it != Game::entities.end()) {
                delete* it;
                Game::entities.erase(it);
            }
        }

        if (asteroidSpawnTime <= 0) {
            Game::entities.push_back(Game::getRandomEntity());
            asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
        }

        Score::scoreText.setString(std::to_string(Score::score));
        window.draw(Score::scoreText);

        DashBar dashBar;

        dashBar.update(min(1 - Player::dashTimer / FileMenager::playerData.dash_time_delay, 1.0));
        dashBar.draw(window);

        if (Game::isGameOver) {
            Game::entities.clear();
            Score::score = 0;
            begin();
        }

        window.display();

    }
}
void WindowBox::begin()
{
    Game::isGameOver = false;
    Game::entities.push_back(new Player());
    asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
}

void WindowBox::init()
{
    Score::init();
}
