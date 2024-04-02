#pragma once
#ifndef ENTITIESLIST_H
#define ENTITIESLIST_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include <list>

class Entity;

class EntitiesList {
public: 
	static std::vector<Entity*> entities;
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	EntitiesList();

	void setEntities(Entity*);
};

#endif