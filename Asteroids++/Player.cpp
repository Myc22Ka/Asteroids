#include "Player.h"
#include "Bullet.h"
#include "EntitiesList.h"
#include <iostream>

constexpr double M_PI = 3.14159265358979323846;

Player::Player() : 
	Entity(sf::Vector2f(FileMenager::playerData.start_position_x, FileMenager::playerData.start_position_y), FileMenager::playerData.start_position_angle),
	shape(sf::LinesStrip, 5), shootTimer(), sprite_change(FileMenager::playerData.sprite_cycle_time)
{
	auto size = FileMenager::playerData.size;
	
	shape[0].position = sf::Vector2f(size, 0);
	shape[1].position = sf::Vector2f(-size, -size);
	shape[2].position = sf::Vector2f(-size /2, 0);
	shape[3].position = sf::Vector2f(-size, size);
	shape[4].position = shape[0].position;

	if (!texture.loadFromFile("./assets/ship.png")) {
		std::cout << "Error: Could not load sprite : " ;
		return;
	}

	spriteRects[0] = sf::IntRect(0, 0, 64, 64);
	spriteRects[1] = sf::IntRect(64, 0, 64, 64);
	spriteRects[2] = sf::IntRect(128, 0, 64, 64);

	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRects[0]);
	sprite.rotate(90);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
}

void Player::render(sf::RenderWindow& window)
{
	sf::Transform transform;
	//window.draw(shape, transform.translate(position).rotate(angle));
	window.draw(sprite, transform.translate(position).rotate(angle));
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
		
		currentSpriteIndex = (currentSpriteIndex + 2) % 4;
		sprite.setTextureRect(spriteRects[currentSpriteIndex]);

		sprite_change2 = FileMenager::playerData.sprite_cycle_time;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		getCurrentSprite(deltaTime, (currentSpriteIndex + 1) % 2);
	}

	if (sprite_change2 > 0.0f) {
		getCurrentSprite(deltaTime, 0);
	}

	position.x = std::min(std::max(position.x, getEntitySize().width / 2), FileMenager::screenData.size_width - getEntitySize().width / 2);
	position.y = std::min(std::max(position.y, getEntitySize().height / 2), FileMenager::screenData.size_height - getEntitySize().height / 2);
}

const Size Player::getEntitySize()
{
	auto width = FileMenager::playerData.size * 2;
	auto height = FileMenager::playerData.size * 2;
	return Size(width, height);
}

sf::Sprite Player::getCurrentSprite(const float &deltaTime, const int &boundry)
{
	sprite_change -= deltaTime;
	if (sprite_change <= 0) {
		currentSpriteIndex = boundry; 
		sprite.setTextureRect(spriteRects[currentSpriteIndex]);
		sprite_change = FileMenager::playerData.sprite_cycle_time;

	}
	return sprite;
}
