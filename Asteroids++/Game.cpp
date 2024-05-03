#include "Game.h"
#include <random>
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"

GameState Game::gameState{ MENU };
bool Game::hitboxesVisibility{ false };

list<Entity*> Game::entities;
list<Particle*> Game::particles;
vector<EntityType> Game::enemies{ EntityType::TYPE_ENEMY_MULTI_ASTEROID, EntityType::TYPE_ENEMY_SINGLE_ASTEROID };

Effect Game::freeze{ FileMenager::timingsData.default_freeze_time, false };
Effect Game::enemySpawn{ FileMenager::timingsData.default_enemy_spawn_time, false };

Game::Game() {}

void Game::addEntity(Entity* entity) {
    entities.push_front(entity);
}

list<Entity*> Game::getEntities() {
    return entities;
}

void Game::foreachEntity(const function<void(Entity*)>& callback)
{
    for (auto& entity : entities) {
        callback(entity);
    }
}

void Game::removeEntity(Entity* entity) {
    entities.remove_if([entity](Entity* e) {
        if (e == entity) {
            entity->setActive(false);
            delete e;
            return true; // Remove this entity from the list
        }
        return false; // Keep this entity in the list
    });
}

void Game::replaceEntity(Entity* entity1, Entity* entity2)
{
    entities.remove(entity1);

    entities.push_front(entity2);
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
    gameState = GAME_OVER;
}

Entity* Game::getRandomEntity(){
    vector<Entity*> enemies = { new MultiAsteroid(), new SingleAsteroid() };

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<size_t> dist(0, enemies.size() - 1);

    auto randomIndex = dist(gen);

    return enemies[randomIndex];
}

list<Particle*> Game::getParticles()
{
    return particles;
}

void Game::addParticle(Particle* particle){
    particles.push_front(particle);
}

void Game::removeParticle(Particle* particle)
{
    particles.remove_if([particle](Entity* e) {
        if (e == particle) {
            particle->setActive(false);
            delete e;
            return true; // Remove this entity from the list
        }
        return false; // Keep this entity in the list
        });
}

bool Game::isEnemy(Entity* entity)
{
    auto isEntityTypeEqual = [&](EntityType type) {
        return type == entity->getEntityType();
        };

    auto it = ranges::find_if(enemies, isEntityTypeEqual);

    return it != enemies.end();
}

bool Game::isEntityInsideGroup(Entity* entity, Groups group)
{
    auto isEntityTypeEqual = [&](EntityType type) {
        return type == entity->getEntityType();
        };

    auto it = ranges::find_if(Effect::groups[group], isEntityTypeEqual);

    return it != Effect::groups[group].end();
}

GameState Game::getGameState()
{
    return gameState;
}

void Game::setGameState(const GameState& newGameState){
    gameState = newGameState;
}

void Game::spawnEnemy(const float& deltaTime) {
	enemySpawn.updateEffectDuration(deltaTime);

	if (enemySpawn.getEffectDuration() <= 0 && !freeze.isEffectActive()) {
		addEntity(getRandomEntity());
		enemySpawn.setEffectDuration(FileMenager::timingsData.default_enemy_spawn_time + Player::playerStats.time * 0.1f);
	}
}