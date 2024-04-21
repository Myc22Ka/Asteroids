#pragma once
#ifndef MULTIASTEROID_H
#define MULTIASTEROID_H

#include "Asteroid.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class MultiAsteroid : public Asteroid
{
public:
	MultiAsteroid();

	const EntityType getEntityType() override;
private:
};
#endif