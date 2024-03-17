module;

#include <SFML/Graphics.hpp>
#include "Player.h"

module WindowBox;

WindowBox::WindowBox() : window(sf::VideoMode(1200, 900), "Asteroids++", sf::Style::Close | sf::Style::Titlebar) {}

void WindowBox::displayWindow()
{
    Player player;
    sf::Clock clock;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }
        // update game ...
        window.clear();
        
        player.draw(window);

        window.display();
    }
}