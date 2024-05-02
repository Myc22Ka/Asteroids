#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Particle.h"
#include <list>
#include <algorithm>
#include <ranges>
#include <functional>
#include "Effect.h"

using namespace std;

class Entity;
class Particle;

enum GameState {
	MENU, 
	MENU_LOADING,
	PLAYING, 
	GAME_OVER
};

class Game {
public:
	Game();

	static bool hitboxesVisibility;

	static list<Particle*> getParticles();
	static void addParticle(Particle* particle);
	static void removeParticle(Particle* particle);

	static list<Entity*> getEntities();
	static void clearEntities();
	static void replaceEntity(Entity* entity1, Entity* entity2);
	static void removeEntity(Entity* entity);
	static void addEntity(Entity* entity);
	static Entity* getRandomEntity();
	static Entity* doesEntityExist(EntityType type);
	static void foreachEntity(const function<void(Entity*)>& callback);

	static bool isEnemy(Entity* entity);

	static bool isEntityInsideGroup(Entity* entity, Groups group);

	static void gameOver();
	static GameState getGameState();
	static void setGameState(const GameState& newGameState);

	static Effect enemySpawn;
	static Effect freeze;
private:
	static list<Entity*> entities;
	static list<Particle*> particles;
	static vector<EntityType> enemies;
	
	static unordered_map<Groups, vector<EntityType>> groups;

	static GameState gameState;
};

#endif
