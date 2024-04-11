#include "Entity.h"
#include "EntitiesList.h"
#include "FileMenager.h"

Entity::Entity(sf::Vector2f position, float angle, int spriteState, int size, sf::Color hitboxColor)
	: position(position), angle(angle), spriteState(spriteState), size(size), hitboxColor(hitboxColor) {}

Entity::~Entity()
{
	delete[] spriteRects;
}

void Entity::playSound(Sounds name)
{
	Sound sound;
	sound.setFileName(name);
	sound.loadAndPlay();
}

void Entity::drawSprite(Sprites name, const int& rotation)
{
	const auto defaultDir = "./assets/";
	const auto extension = ".png";
	const auto defaultSize = FileMenager::playerData.size;

	std::string filename;
	switch (name) {
	case Sprites::SHIP:
		filename = "ship";
		break;
	case Sprites::ASTEROID:
		filename = "asteroid";
		break;
	case Sprites::BULLET:
		filename = "bullet";
		break;
	default:
		std::cerr << "Error: Invalid Sprite Name\n";
		return;
	}

	if (!texture.loadFromFile(defaultDir + filename + extension)) return;

	const int n = texture.getSize().x / defaultSize;

	spriteRects = new sf::IntRect[n];

	int currentSprite = 0;

	for (int i = 0; i < n; i++) {
		spriteRects[i] = sf::IntRect(currentSprite, 0, defaultSize, defaultSize);
		currentSprite += defaultSize;
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRects[0]);
	sprite.rotate(rotation);

	const float scale = size / defaultSize;
	sprite.setScale(scale, scale);

	sf::Rect center = sprite.getLocalBounds();

	sprite.setOrigin((int)center.width >> 1, (int)center.height >> 1);
}

void Entity::setSprite(const int& state)
{
	sprite.setTextureRect(spriteRects[state]);
}

void Entity::drawHitboxes()
{
	const auto newSize = size >> 1;

	shape.setRadius(newSize);
	sf::Vector2f center(newSize, newSize);

	shape.setOrigin(center);

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(hitboxColor);
	shape.setOutlineThickness(1.5f);
}