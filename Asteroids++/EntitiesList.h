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
	EntitiesList();

	static std::vector<Entity*> entities;
	static std::list<std::vector<Entity*>::iterator> toRemoveList;
	static std::list<Entity*> toAddList;

	void setEntities(Entity*);
};

#endif