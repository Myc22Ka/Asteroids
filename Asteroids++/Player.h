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
private:
	sf::VertexArray shape;
};

#endif