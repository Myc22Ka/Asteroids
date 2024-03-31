#include "EntitiesList.h"

std::vector<Entity*> EntitiesList::entities;

EntitiesList::EntitiesList() {}

void EntitiesList::setEntities(Entity* entity) {
    entities.push_back(entity);
}
