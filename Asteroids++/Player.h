#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
	Player();

	void draw(sf::RenderWindow& window);

	sf::Vector2f position;
	float angle;
private:
	sf::VertexArray shape;
	int size = 20;
};

#endif