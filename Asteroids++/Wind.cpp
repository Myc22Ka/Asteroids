#include "Wind.h"

Wind::Wind() : Entity(getRandomPosition(), 0, Asteroid::getRandomValue(64), Color::Yellow, getSprite(Sprites::WIND))
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
}

const Vector2f Wind::getRandomPosition() const 
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> xAxis(radius, FileMenager::screenData.size_width - radius);
	uniform_real_distribution<double> yAxis(radius, FileMenager::screenData.size_height - radius);

	return Vector2f(xAxis(gen), yAxis(gen));
}

void Wind::render(RenderWindow& window)
{
	window.draw(spriteInfo.sprite, Transform().translate(position));
}

void Wind::update(float deltaTime)
{
	position.x -= 5;
	setSpriteFullCycle(deltaTime);
}

const EntityType Wind::getEntityType()
{
	return EntityType::TYPE_EVENT_WIND;
}

void Wind::collisionDetection() {}