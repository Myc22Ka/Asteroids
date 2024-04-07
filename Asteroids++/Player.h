#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntitiesList.h"
#include "FileMenager.h"

import WindowBox;

class Player: public Entity, public WindowBox {
public:
	Player();

	void render(sf::RenderWindow&) override;
	void update(float) override;
	const Size getEntitySize() override;
	sf::Sprite getCurrentSprite(const float&, const int&);

private:
	sf::VertexArray shape;
	float shootTimer;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect spriteRects[3];
	float sprite_change;
	int currentSpriteIndex = 0;
	int sprite_change2;
};

#endif