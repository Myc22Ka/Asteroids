#pragma once
#ifndef ENTITIESLIST_H
#define ENTITIESLIST_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

class Entity;

class EntitiesList {
public: 
	static std::vector<Entity*> entities;
	EntitiesList();

	void setEntities(Entity*);
};

#endif