#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "EntitiesList.h"
#include "Sound.h"
#include <iostream>

constexpr double M_PI = 3.14159265358979323846;

Player::Player() : 
	Entity(sf::Vector2f(FileMenager::playerData.start_position_x, FileMenager::playerData.start_position_y), FileMenager::playerData.start_position_angle),
	shape(FileMenager::playerData.size), shootTimer(), size((int)FileMenager::playerData.size >> 1)
{
	shape.setRadius(size);
	sf::Vector2f center(size, size);

	shape.setOrigin(center);

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(1.0f);

	if (!texture.loadFromFile("./assets/ship.png")) {
		std::cout << "Error: Could not load sprite : ";
		return;
	}

	const auto spriteSize = size << 1;

	spriteRects[0] = sf::IntRect(0, 0, spriteSize, spriteSize);

	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRects[0]);
	sprite.rotate(45);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
}

void Player::render(sf::RenderWindow& window)
{
	sf::Transform transform;
	window.draw(sprite, transform.translate(position).rotate(angle));
	//window.draw(shape, transform);
}

void Player::update(float deltaTime) {
	const auto turnSpeed = FileMenager::playerData.turn_speed;
	const auto speed = FileMenager::playerData.speed;
	shootTimer -= deltaTime;

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
		EntitiesList::toAddList.push_back(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));

		playSound(Names::LASER_SHOOT);
	}

	const float size = (float)(this->size >> 1);

	position.x = std::min(std::max(position.x, size), FileMenager::screenData.size_width - size);
	position.y = std::min(std::max(position.y, size), FileMenager::screenData.size_height - size);

	for (size_t i = 0; i < EntitiesList::entities.size(); i++)
	{
		if (typeid(*EntitiesList::entities[i]) == typeid(Asteroid)) {
			Asteroid* asteroid = dynamic_cast<Asteroid*>(EntitiesList::entities[i]);

			if (physics::intersects(position, this->size, asteroid->position, asteroid->size)) {
				playSound(Names::EXPLOSION);
				gameOver();
			}
		}
	}
}

const EntityType Player::getEntityType()
{
	return EntityType::TYPE_PLAYER;
}
