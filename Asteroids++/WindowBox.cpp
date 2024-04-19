module;

#include "Player.h"
#include "Asteroid.h"
#include <iostream>
#include "Score.h"
#include "Physics.h"
#include "ProgressCircle.h"

module WindowBox;

float WindowBox::asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;

WindowBox::WindowBox() {}

void WindowBox::displayWindow()
{
    window.create(sf::VideoMode(FileMenager::screenData.size_width, FileMenager::screenData.size_height), "Asteroids++", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::Clock clock;
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

        float deltaTime = clock.restart().asSeconds();

        Game::toAddList.clear();
        Game::toRemoveList.clear();
        window.clear();

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
            Game::entities.push_back(new Asteroid());
            asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
        }

        Score::scoreText.setString(std::to_string(Score::score));
        window.draw(Score::scoreText);

        ProgressCircle dashTimer(50.0f);
        dashTimer.setValue(1 - Player::dashTimer / FileMenager::playerData.dash_time_delay);
        window.draw(dashTimer);

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
