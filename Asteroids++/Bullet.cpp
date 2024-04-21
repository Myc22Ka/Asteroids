#include "Bullet.h"
#include "SingleAsteroid.h"
#include "MultiAsteroid.h"
#include "Physics.h"
#include "Score.h"
#include "SoundData.h"
#include "Pickup.h"

Bullet::Bullet(Vector2f position, Vector2f direction, const float& angle) :
    direction(direction), 
    Entity(position, angle, Player::playerStats.bulletSize, Color::Green, getSprite(Sprites::BULLET)),
    lifeTime(FileMenager::playerData.bullet_lifetime)
{
    setRotation(spriteInfo.sprite, angle);
    drawHitboxes();

    scaleSprite(spriteInfo.sprite, FileMenager::playerData.bullet_size, size);
}

void Bullet::update(double deltaTime)
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

const EntityType Bullet::getEntityType()
{
    return EntityType::TYPE_BULLET;
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

    if (propability > 0.25) return;

    if (propability < 0.02) {
        Game::addToEntities(new Pickup(position, getSprite(Pickup::pickups[3])));
        return;
    }
    if (propability < 0.08) {
        Game::addToEntities(new Pickup(position, getSprite(Pickup::pickups[2])));
        return;
    }
    if (propability < 0.15) {
        Game::addToEntities(new Pickup(position, getSprite(Pickup::pickups[1])));
        return;
    }
    if (propability < 0.25) {
        Game::addToEntities(new Pickup(position, getSprite(Pickup::pickups[0])));
        return;
    }
    
}

void Bullet::singleAsteroidHit(const int& i)
{
    SingleAsteroid* asteroid = dynamic_cast<SingleAsteroid*>(Game::entities[i]);
    
    if (physics::intersects(position, radius, asteroid->position, asteroid->radius) && lifeTime > 0) {
        lifeTime = 0;
        asteroid->health -= Player::playerStats.bulletDamage;
    
        if (asteroid->health <= 0) {
            Game::toAddList.push_back(new Explosion(asteroid->position, asteroid->size));
    
            Game::removeEntity(asteroid);

            spawnPickup(asteroid->position);
    
            Score::score += 10;
            SoundData::play(Sounds::EXPLOSION);
        }
    }    
}

void Bullet::multiAsteroidHit(const int& i)
{
    MultiAsteroid* asteroid = dynamic_cast<MultiAsteroid*>(Game::entities[i]);
    
    if (physics::intersects(position, radius, asteroid->position, asteroid->radius) && lifeTime > 0) {
        lifeTime = 0;
        asteroid->health -= Player::playerStats.bulletDamage;
    
        if (asteroid->health <= 0) {
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
    }
}
