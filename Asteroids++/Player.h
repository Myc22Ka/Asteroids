#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

import WindowBox;

class Player: public WindowBox {
public:
	Player();

	void draw(sf::RenderWindow& window);
	void update(float deltaTime);

	sf::Vector2f position;
	float angle;
private:
	sf::VertexArray shape;
};

#endif