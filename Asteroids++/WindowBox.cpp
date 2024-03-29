module;

#include <SFML/Graphics.hpp>
#include "Player.h"

module WindowBox;

WindowBox::WindowBox() {
    setFileName("config.txt");
    setDataFromFile();
}

void WindowBox::displayWindow()
{
    window.create(sf::VideoMode(getPropertyValue("screen_size_height"), getPropertyValue("screen_size_width")), "Asteroids++", sf::Style::Close | sf::Style::Titlebar);

    Player player;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }

            float deltaTime = clock.restart().asSeconds();

            player.update(deltaTime);

            window.clear();

            player.draw(window);

            window.display();
        
    }
}