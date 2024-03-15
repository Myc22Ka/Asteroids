#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids++", sf::Style::Close | sf::Style::Titlebar);
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
        // draw game ...
        window.display();
    }

    std::cout << "Hello World!\n";
}