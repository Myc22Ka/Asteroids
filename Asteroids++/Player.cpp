#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "EntitiesList.h"
#include "Sound.h"
#include <iostream>

constexpr double M_PI = 3.14159265358979323846;

Player::Player() : 
	Entity(sf::Vector2f(FileMenager::playerData.start_position_x, FileMenager::playerData.start_position_y), FileMenager::playerData.start_position_angle, 0, FileMenager::playerData.size, sf::Color::Blue), shootTimer()
{
	spriteLifeTime = FileMenager::playerData.sprite_cycle_time;

	drawHitboxes();

	drawSprite(Sprites::SHIP, 45);
}

void Player::render(sf::RenderWindow& window)
{
	sf::Transform transform;
	window.draw(sprite, transform.translate(position).rotate(angle));
	if(WindowBox::hitboxesVisibility) window.draw(shape, transform);
}

void Player::update(float deltaTime) {
	const auto turnSpeed = FileMenager::playerData.turn_speed;
	const auto speed = FileMenager::playerData.speed;
	shootTimer -= deltaTime;
	spriteLifeTime -= deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= turnSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += turnSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		float radians = angle * (M_PI / 180.0f);

		position.x += cos(radians) * speed * deltaTime;
		position.y += sin(radians) * speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0) {
		shootTimer = FileMenager::playerData.bullet_shoot_delay;
		float radians = angle * (M_PI / 180.0f);
		EntitiesList::toAddList.push_back(new Bullet(position, sf::Vector2f(cos(radians), sin(radians)), angle));

		playSound(Sounds::LASER_SHOOT);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spriteLifeTime <= 0) {
		spriteLifeTime = FileMenager::playerData.sprite_cycle_time;
		spriteState = (spriteState + 1) % 3;
		setSprite(spriteState);
	}

	collisionDetection();
}

const EntityType Player::getEntityType()
{
	return EntityType::TYPE_PLAYER;
}

void Player::collisionDetection()
{
	const int radius = size >> 1;
	const float radiusf = size >> 1;

	position.x = std::min(std::max(position.x, radiusf), FileMenager::screenData.size_width - radius);
	position.y = std::min(std::max(position.y, radiusf), FileMenager::screenData.size_height - radius);

	for (size_t i = 0; i < EntitiesList::entities.size(); i++)
	{
		if (typeid(*EntitiesList::entities[i]) == typeid(Asteroid)) {
			Asteroid* asteroid = dynamic_cast<Asteroid*>(EntitiesList::entities[i]);

			if (physics::intersects(position, radius, asteroid->position, asteroid->size >> 1)) {
				playSound(Sounds::EXPLOSION);
				gameOver();
			}
		}
	}
}