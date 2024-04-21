#include "Bullet.h"
#include "SingleAsteroid.h"
#include "MultiAsteroid.h"
#include "Physics.h"
#include "Score.h"
#include "SoundData.h"


Bullet::Bullet(Vector2f position, Vector2f direction, const float& angle) :
    direction(direction), 
    Entity(position, angle, FileMenager::playerData.bullet_size, Color::Green, getSprite(Sprites::BULLET)),
    lifeTime(FileMenager::playerData.bullet_lifetime)
{
    setRotation(spriteInfo.sprite, angle);
    damage = 50;
    drawHitboxes();
}

void Bullet::update(double deltaTime)
{
    auto bulletSpeed = FileMenager::playerData.bullet_speed;
    lifeTime -= deltaTime;
    position += Vector2f(direction.x * bulletSpeed * deltaTime, direction.y * bulletSpeed * deltaTime);
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

void Bullet::singleAsteroidHit(const int& i)
{
    SingleAsteroid* asteroid = dynamic_cast<SingleAsteroid*>(Game::entities[i]);
    
    if (physics::intersects(position, radius, asteroid->position, asteroid->radius) && lifeTime > 0) {
        lifeTime = 0;
        asteroid->health -= damage;
    
        if (asteroid->health <= 0) {
            Game::toAddList.push_back(new Explosion(asteroid->position, asteroid->size));
    
            Game::removeEntity(asteroid);
    
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
        asteroid->health -= damage;
    
        if (asteroid->health <= 0) {
            Game::toAddList.push_back(new Explosion(asteroid->position, asteroid->size));
    
            Game::removeEntity(asteroid);

            float distance = 50.0f; // Adjust as needed

            sf::Vector2f position1 = asteroid->position + sf::Vector2f(0.0f, -distance); // Above
            sf::Vector2f position2 = asteroid->position + sf::Vector2f(-distance * sqrt(3) / 2, distance / 2); // Bottom-left
            sf::Vector2f position3 = asteroid->position + sf::Vector2f(distance * sqrt(3) / 2, distance / 2); // Bottom-right

            Game::addToEntities(new SingleAsteroid(position1, sf::Vector2f(0.0f, -1)));
            Game::addToEntities(new SingleAsteroid(position2, sf::Vector2f(-1 * sqrt(3) / 2, 1 / 2)));
            Game::addToEntities(new SingleAsteroid(position3, sf::Vector2f(1 * sqrt(3) / 2, 1 / 2)));

    
            Score::score += 20;
            SoundData::play(Sounds::EXPLOSION);
        }
    }
}
