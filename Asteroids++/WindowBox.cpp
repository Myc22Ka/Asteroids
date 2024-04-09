module;

#include "Player.h"
#include "Asteroid.h"
#include <iostream>
#include "Score.h"
#include "Physics.h"

module WindowBox;

WindowBox::WindowBox() {}

void WindowBox::displayWindow()
{
    window.create(sf::VideoMode(FileMenager::screenData.size_width, FileMenager::screenData.size_height), "Asteroids++", sf::Style::Close | sf::Style::Titlebar);
    Score::init();

    sf::Clock clock;

    EntitiesList::entities.push_back(new Player());

    float asteroidSpawnTime = FileMenager::enemiesData.asteroid_spawn_time;

    sf::VertexArray poly1(sf::LinesStrip);
    sf::VertexArray poly2(sf::LinesStrip);

    enum { POLY_1, POLY_2, TEST } state = POLY_1;
    
    while (window.isOpen()) {
        sf::Event e{};
        float deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(window);
                if (state == POLY_1) poly1.append(sf::Vertex(pos, sf::Color::White));
                else if (state == POLY_2) poly2.append(sf::Vertex(pos, sf::Color::White));
            }
            else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
                if (state == POLY_1 && poly1.getVertexCount() > 0) {
                    state = POLY_2;
                    poly1.append(poly1[0]);
                }
                else if (state == POLY_2 && poly2.getVertexCount() > 0) {
                    state = TEST;
                    poly2.append(poly2[0]);

                    if (physics::intersects(poly1, poly2)) {
                        std::cout << "intersect\n";
                    }
                }
                else
                {
                    state = POLY_1;
                    poly1.clear();
                    poly2.clear();
                }
            }
        }

        window.clear();

        window.draw(poly1);
        window.draw(poly2);

        window.display();
        
    }
}
