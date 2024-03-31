module;

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "EntitiesList.h"
#include <iostream>

module WindowBox;

WindowBox::WindowBox() {}

void WindowBox::displayWindow()
{
    window.create(sf::VideoMode(getValueFromProperty("screen_size_height"), getValueFromProperty("screen_size_width")), "Asteroids++", sf::Style::Close | sf::Style::Titlebar);

    sf::Clock clock;

    EntitiesList::entities.push_back(new Player());

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();


        for (size_t i = 0; i < EntitiesList::entities.size(); i++)
        {
            EntitiesList::entities[i]->update(deltaTime);
            EntitiesList::entities[i]->render(window);
        }

        std::cout << EntitiesList::entities.size() << std::endl;

        window.display();
        
    }
}