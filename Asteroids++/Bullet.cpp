#include "Bullet.h"
#include "SingleAsteroid.h"
#include "MultiAsteroid.h"
#include "Physics.h"
#include "Score.h"
#include "SoundData.h"
#include "Pickup.h"

bool Bullet::piercing{ false };

Bullet::Bullet(Vector2f position, Vector2f direction, const float& angle) :
    direction(direction), 
    Entity(position, angle, Player::playerStats.bulletSize, Color::Green, getSprite(Sprites::BULLET)),
    lifeTime(FileMenager::playerData.bullet_lifetime)
{
}

void Bullet::update(float deltaTime)
{
    lifeTime -= deltaTime;
    position += Vector2f(direction.x * Player::playerStats.bulletSpeed * deltaTime, direction.y * Player::playerStats.bulletSpeed * deltaTime);
    if (lifeTime <= 0) Game::removeEntity(this);

    collisionDetection();
}

void Bullet::render(RenderWindow& window)
{
    Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position));
    if (Game::hitboxesVisibility) window.draw(shape, transform);
}

void Bullet::collisionDetection()
{
    for (size_t i = 0; i < Game::entities.size(); i++)
    {
        if (typeid(*Game::entities[i]) == typeid(SingleAsteroid)) singleAsteroidHit(i);
        
        if (typeid(*Game::entities[i]) == typeid(MultiAsteroid)) multiAsteroidHit(i);
    }
}

void Bullet::spawnPickup(const Vector2f& position)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    auto propability = dist(gen);

    if (propability > 0.5) return;

    if (propability < 0.1) {
        Game::addToEntities(new Pickup(position, getSprite(Sprites::CHEST)));
        return;
    }
    if (propability < 0.2) {
        Game::addToEntities(new Pickup(position, getSprite(Sprites::PICKUP_4)));
        return;
    }
    if (propability < 0.3) {
        Game::addToEntities(new Pickup(position, getSprite(Sprites::PICKUP_3)));
        return;
    }
    if (propability < 0.4) {
        Game::addToEntities(new Pickup(position, getSprite(Sprites::PICKUP_2)));
        return;
    }
    if (propability < 0.5) {
        Game::addToEntities(new Pickup(position, getSprite(Sprites::PICKUP_1)));
        return;
    }
    
}

void Bullet::destroySingleAsteroid(const int& i)
{
    SingleAsteroid* asteroid = dynamic_cast<SingleAsteroid*>(Game::entities[i]);

    Game::toAddList.push_back(new Explosion(asteroid->position, asteroid->size));

    Game::removeEntity(asteroid);

    spawnPickup(asteroid->position);

    Score::score += 10;
    SoundData::play(Sounds::EXPLOSION);
}

void Bullet::destroyMultiAsteroid(const int& i)
{
    MultiAsteroid* asteroid = dynamic_cast<MultiAsteroid*>(Game::entities[i]);

    Game::toAddList.push_back(new Explosion(asteroid->position, asteroid->size));

    Game::removeEntity(asteroid);

    auto asteroid1 = new SingleAsteroid(asteroid->position, asteroid->getRandomDirection());
    auto asteroid2 = new SingleAsteroid(Vector2f(asteroid->position.x + asteroid1->radius, asteroid->position.y + asteroid1->radius), asteroid->getRandomDirection());

    const auto bounceDirection = physics::bounceDirection(asteroid1, asteroid2, 1.0f);

    asteroid1->position += bounceDirection.second;
    asteroid2->position -= bounceDirection.second;

    asteroid1->direction -= bounceDirection.first;
    asteroid2->direction += bounceDirection.first;

    Game::addToEntities(new SingleAsteroid(asteroid1->position, asteroid1->direction));
    Game::addToEntities(new SingleAsteroid(asteroid2->position, asteroid2->direction));

    Score::score += 20;
    SoundData::play(Sounds::EXPLOSION);
}
