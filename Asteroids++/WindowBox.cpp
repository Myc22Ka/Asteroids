module;

#include "Player.h"
#include "Asteroid.h"
#include <iostream>
#include "Score.h"
#include "Physics.h"

module WindowBox;

bool WindowBox::isGameOver{};
float WindowBox::asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;

WindowBox::WindowBox() {}

void WindowBox::displayWindow()
{
    window.create(sf::VideoMode(FileMenager::screenData.size_width, FileMenager::screenData.size_height), "Asteroids++", sf::Style::Close | sf::Style::Titlebar);

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

        for (const auto& it : EntitiesList::toRemoveList)
        {
            delete* it;
            EntitiesList::entities.erase(it);
        }

        for (auto& ptr : EntitiesList::toAddList)
        {
            EntitiesList::entities.push_back(ptr);
        }

        if (asteroidSpawnTime <= 0) {
            EntitiesList::entities.push_back(new Asteroid());
            asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;
        }

        Score::scoreText.setString(std::to_string(Score::score));
        window.draw(Score::scoreText);

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
