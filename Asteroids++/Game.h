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

using namespace std;

class Entity;
class Particle;

class Game {
public:
	Game();

	static bool hitboxesVisibility;
	static bool isGameOver;

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

	static void gameOver();
private:
	static list<Entity*> entities;
	static list<Particle*> particles;
	static vector<EntityType> enemies;
};

#endif
