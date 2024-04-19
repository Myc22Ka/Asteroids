#include "Game.h"

vector<Entity*> Game::entities;
list<vector<Entity*>::iterator> Game::toRemoveList;
list<Entity*> Game::toAddList;
bool Game::isGameOver{ false };
bool Game::hitboxesVisibility{ false };

Game::Game() {}

void Game::setEntity(Entity* entity) {
    entities.push_back(entity);
}

void Game::removeEntity(Entity* entity)
{
    toRemoveList.push_back(ranges::find(Game::entities, entity));
}

void Game::addToEntities(Entity* entity) {
    toAddList.push_back(entity);
}

void Game::clearEntities(){
    entities.clear();
}

Entity* Game::doesEntityExist(EntityType type) {
    auto player = ranges::find_if(entities, [type](Entity* entity) {
        return entity->getEntityType() == type;
        });

    if (player != entities.end()) {
        return *player;
    }
        
    return nullptr;
}

void Game::gameOver(){
    isGameOver = true;
}
