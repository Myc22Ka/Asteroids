module;

#include "Player.h"
#include "Asteroid.h"
#include <iostream>
#include "Score.h"
#include "Physics.h"
#include "ProgressCircle.h"

module WindowBox;

bool WindowBox::isGameOver{};
float WindowBox::asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
bool WindowBox::hitboxesVisibility{ false };

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
                    std::cout << EntitiesList::entities.size() << std::endl;
                }
                if (e.key.code == sf::Keyboard::H) {
                    WindowBox::hitboxesVisibility = !WindowBox::hitboxesVisibility;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        EntitiesList::toAddList.clear();
        EntitiesList::toRemoveList.clear();
        window.clear();

        asteroidSpawnTime -= deltaTime;

        for (size_t i = 0; i < EntitiesList::entities.size(); i++)
        {
            EntitiesList::entities[i]->update(deltaTime);
            EntitiesList::entities[i]->render(window);
        }

        std::vector<Entity*> entitiesToAdd;
        std::vector<Entity*> entitiesToRemove;

        for (auto& ptr : EntitiesList::toAddList) {
            entitiesToAdd.push_back(ptr);
        }
        EntitiesList::toAddList.clear();

        for (auto& ptr : EntitiesList::toRemoveList) {
            entitiesToRemove.push_back(*ptr);
        }
        EntitiesList::toRemoveList.clear();

        for (auto ptr : entitiesToAdd) {
            EntitiesList::entities.push_back(ptr);
        }

        for (auto ptr : entitiesToRemove) {
            auto it = std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), ptr);
            if (it != EntitiesList::entities.end()) {
                delete* it;
                EntitiesList::entities.erase(it);
            }
        }

        if (asteroidSpawnTime <= 0) {
            EntitiesList::entities.push_back(new Asteroid());
            asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
        }

        Score::scoreText.setString(std::to_string(Score::score));
        window.draw(Score::scoreText);

        ProgressCircle dashTimer(50.0f);
        dashTimer.setValue(1 - Player::dashTimer / FileMenager::playerData.dash_time_delay);
        window.draw(dashTimer);

        if (isGameOver) {
            EntitiesList::entities.clear();
            Score::score = 0;
            begin();
        }

        window.display();

    }
}

void WindowBox::gameOver()
{
    isGameOver = true;
}

void WindowBox::begin()
{
    isGameOver = false;
    EntitiesList::entities.push_back(new Player());
    asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
}

void WindowBox::init()
{
    Score::init();
}
