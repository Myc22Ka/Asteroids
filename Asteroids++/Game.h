#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include <list>
#include <algorithm>
#include <ranges>

using namespace std;

class Entity;

class Game {
public: 
	Game();

	static bool hitboxesVisibility;
	static bool isGameOver;
	static vector<Entity*> entities;
	static list<vector<Entity*>::iterator> toRemoveList;
	static list<Entity*> toAddList;

	void setEntity(Entity*);
	static void clearEntities();
	static void removeEntity(Entity*);
	static void addToEntities(Entity*);
	static Entity* doesEntityExist(EntityType type);

	static Entity* getRandomEntity();

	static void gameOver();
private:
};

#endif