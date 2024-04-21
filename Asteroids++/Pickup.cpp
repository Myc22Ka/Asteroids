#include "Pickup.h"

Pickup::Pickup(Vector2f position): Entity(position, 0, 64, Color::Cyan, getSprite(Sprites::PICKUP)),
lifeTime(5)
{
	size <<= 1;
	drawHitboxes();

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
}

void Pickup::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position));
	if (Game::hitboxesVisibility) window.draw(shape, transform);
}

void Pickup::update(double deltaTime)
{
	lifeTime -= deltaTime;
	if (lifeTime <= 0) Game::removeEntity(this);
	setSpriteFullCycle(deltaTime);

	collisionDetection();
}

const EntityType Pickup::getEntityType()
{
	return EntityType::TYPE_PICKUP;
}

void Pickup::collisionDetection()
{
	for (const auto& entity : Game::entities) {
		if (entity->getEntityType() == EntityType::TYPE_PLAYER && entity != this) {
			Player* player = dynamic_cast<Player*>(entity);

			if (!player) return;

			if (physics::intersects(this->position, this->radius, player->position, player->radius) && lifeTime > 0) {
				lifeTime = 0;

				if(Player::playerStats.shootOffset < 0.1) Player::playerStats.shootOffset += 0.01;
				SoundData::play(Sounds::PICKUP);
			}
		}
	}
}