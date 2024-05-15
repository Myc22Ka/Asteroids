#include "Game.h"
#include <random>
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"
#include "Comet.h"
#include "Invader.h"
#include "Strauner.h"

GameState Game::gameState{ MENU };
bool Game::hitboxesVisibility{ false };

list<Entity*> Game::entities;
list<Particle*> Game::particles;
vector<EntityType> Game::enemies{ EntityType::TYPE_ENEMY, EntityType::TYPE_ENEMY_BULLET };
int Game::maxLevel{ 5 };
int Game::level{ 1 };

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

Entity* Game::findEntity(Sprites spriteType) {
    for (auto& entity : entities)
        if (entity->spriteInfo.spriteType == spriteType) return entity;

    return nullptr;
}

void Game::gameOver(){
    gameState = GAME_OVER;
}

Entity* Game::getRandomEntity(const int& startIndex, const int& endIndex) {
    const vector<EnemySpawn> enemiesList = {
        { new Strauner(), 0.1, true},
        { new Invader(), 0.25, false },
        { new Comet(), 0.4, true },
        { new MultiAsteroid(), 0.5, false },
        { new SingleAsteroid() , 1, false }
    };

    if (startIndex < 0 || endIndex >= enemiesList.size() || startIndex > endIndex) return nullptr;

    const auto dice = physics::rollDice();

    for (int i = startIndex; i <= endIndex; ++i) {
        const auto& [entity, chance, onlyOne] = enemiesList[i];

        if (onlyOne && findEntity(entity->spriteInfo.spriteType) == nullptr && dice < chance) {
            return entity;
        }
        if (!onlyOne && dice < chance) {
            return entity;
        }
    }

    return nullptr;
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

void Game::clearParticles() {
    particles.clear();
}

const bool Game::getEvil(Entity* entity)
{
    for (auto& enemy : enemies)
        if (entity->getEntityType() == enemy) return true;

    return false;
}

const bool Game::isEnemy(Entity* entity) {
    return entity->getEntityType() == EntityType::TYPE_ENEMY;
}

GameState Game::getGameState()
{
    return gameState;
}

void Game::setGameState(const GameState& newGameState){
    gameState = newGameState;
}

void Game::spawnEnemy(const float& deltaTime) {
	if (gameState == PAUSED) return;

	enemySpawn.updateEffectDuration(deltaTime);

	if (enemySpawn.getEffectDuration() <= 0 && !freeze.isEffectActive()) {
        const auto entity = getRandomEntity(maxLevel - level, maxLevel - 1);

		if(entity) addEntity(entity);
		enemySpawn.setEffectDuration(FileMenager::timingsData.default_enemy_spawn_time + Player::playerStats.time * 0.1f - level * 0.1f);
	}
}