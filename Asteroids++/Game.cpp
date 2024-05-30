#include "Game.h"
#include <random>
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"
#include "Comet.h"
#include "Invader.h"
#include "Strauner.h"
#include "Tower.h"
#include "MenuLoader.h"
#include "Menu.h"
#include "HighScoreTable.h"
#include "GameOver.h"
#include "GamePause.h"
#include "DeathScreen.h"
#include "BlackHole.h"

GameState Game::gameState{ MENU };
bool Game::hitboxesVisibility{ false };

Page* Game::currentPage = nullptr;

list<Entity*> Game::entities;
list<Particle*> Game::particles;
int Game::maxLevel{ 7 };
int Game::level{ 4 };

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

Entity* Game::getRandomEntity(const int& startIndex, const int& endIndex) {
    const vector<EnemySpawn> enemiesList = {
        {new Tower(), 0.18, false},
        {new Strauner(), 0.19, true},
        {new Invader(), 0.5, false},
        {new BlackHole(), 0.6, false},
        {new Comet(), 0.7, true},
        {new MultiAsteroid(), 0.8, false},
        {new SingleAsteroid(), 1.0, false}
    };

    if (startIndex < 0 || endIndex >= enemiesList.size() || startIndex > endIndex) {
        return nullptr;
    }

    double totalChance = 0.0;
    for (int i = startIndex; i <= endIndex; ++i) {
        totalChance += enemiesList[i].chance;
    }

    double dice = physics::rollDice() * totalChance;

    double cumulativeChance = 0.0;
    for (int i = startIndex; i <= endIndex; ++i) {
        const auto& [entity, chance, onlyOne] = enemiesList[i];
        cumulativeChance += chance;

        if (dice <= cumulativeChance) {
            if (onlyOne) {
                if (findEntity(entity->spriteInfo.spriteType) == nullptr) {
                    return entity;
                }
            }
            else {
                return entity;
            }
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

const bool Game::isEntityInsideGruop(Entity* entity, const vector<Sprites>& group)
{
    return ranges::find(group, entity->getSpriteType()) != group.end();
}

const bool Game::isEntityInsideGruop(Entity* entity, const vector<EntityType>& group)
{
    return ranges::find(group, entity->getEntityType()) != group.end();
}

GameState Game::getGameState()
{
    return gameState;
}

void Game::setGameState(const GameState& newGameState){
    switch (newGameState)
    {
    case MENU_LOADING:
        setCurrentPage(new MenuLoader());
        break;
    case MENU:
        setCurrentPage(new Menu());
        break;
    case GAME_OVER:
        if(DeathScreen::isScreenOver()) setCurrentPage(new GameOver());
        break;
    case MENU_HIGHSCORE:
        setCurrentPage(new HighScoreTable());
        break;
    default:
        break;
    }
    gameState = newGameState;
}

void Game::spawnEnemy(const float& deltaTime) {
	if (gameState != PLAYING && gameState != FREZZE && gameState != WIND) return;

	enemySpawn.updateEffectDuration(deltaTime);

	if (enemySpawn.getEffectDuration() <= 0 && !freeze.isEffectActive()) {
        const auto entity = getRandomEntity(maxLevel - level, maxLevel - 1);
        //auto entity = new BlackHole();

		if(entity) addEntity(entity);
		enemySpawn.setEffectDuration(FileMenager::timingsData.default_enemy_spawn_time + Player::playerStats.time * 0.1f - level * 0.1f - floor(Score::getScore() >> 10) * 0.01f);
        //enemySpawn.setEffectDuration(100000000.0f);
	}
}

void Game::setCurrentPage(Page* newPage)
{
    delete currentPage;
    currentPage = newPage;
}

void Game::runCurrentPage(float deltaTime, RenderWindow& window)
{
    if (!currentPage) return;

    currentPage->run(deltaTime, window);
}

void Game::navigate(Event& e){
    currentPage->navigator(e);
}