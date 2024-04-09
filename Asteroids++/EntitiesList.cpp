#include "EntitiesList.h"

std::vector<Entity*> EntitiesList::entities;
std::list<std::vector<Entity*>::iterator> EntitiesList::toRemoveList;
std::list<Entity*> EntitiesList::toAddList;

EntitiesList::EntitiesList() {}

void EntitiesList::setEntities(Entity* entity) {
    entities.push_back(entity);
}
