#include "Pickup.h"

vector<Sprites> Pickup::pickups{ Sprites::PICKUP_1, Sprites::PICKUP_2, Sprites::PICKUP_3, Sprites::PICKUP_4 };

Pickup::Pickup(Vector2f position, SpriteInfo s): Entity(position, 0, 64, Color::Cyan, s),
lifeTime(5)
{
	collected = getSprite(Sprites::COLLECTED);
	drawHitboxes(size >> 2);

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
	collected.currentSpriteLifeTime -= deltaTime;
	lifeTime -= deltaTime;
	if (lifeTime <= 0) Game::removeEntity(this);
	setSpriteFullCycle(deltaTime);

	collisionDetection();
}

const EntityType Pickup::getEntityType()
{
	switch (spriteInfo.spriteType)
	{
	case Sprites::PICKUP_1:
		return EntityType::TYPE_PICKUP_1;
	case Sprites::PICKUP_2:
		return EntityType::TYPE_PICKUP_2;
	case Sprites::PICKUP_3:
		return EntityType::TYPE_PICKUP_3;
	case Sprites::PICKUP_4:
		return EntityType::TYPE_PICKUP_4;
	default:
		return EntityType();
	}
}

void Pickup::collisionDetection()
{
	for (const auto& entity : Game::entities) {
		if (entity->getEntityType() == EntityType::TYPE_PLAYER && entity != this) {
			Player* player = dynamic_cast<Player*>(entity);

			if (!player) return;

			if (physics::intersects(this->position, this->radius, player->position, player->radius) && lifeTime > 0) {
				lifeTime = 0;

				switch (getEntityType())
				{
				case EntityType::TYPE_PICKUP_1:
					if(Player::playerStats.shootOffset >= 0.11) Player::playerStats.shootOffset -= 0.01;
					Score::score += 10;
					break;
				case EntityType::TYPE_PICKUP_2:
					Player::playerStats.bulletDamage += 50;
					Score::score += 20;
					break;
				case EntityType::TYPE_PICKUP_3:
					if(Player::playerStats.bulletSize <= 50) Player::playerStats.bulletSize += 1;
					Score::score += 50;
					break;
				case EntityType::TYPE_PICKUP_4:
					if (Player::playerStats.speed < 350) {
						Player::playerStats.speed += 10;
						Player::playerStats.turnSpeed += 5;
					}
					Score::score += 100;
					break;
				}
				SoundData::play(Sounds::PICKUP);
				Game::addToEntities(new Explosion(this->position, this->size, collected));

				cout << Player::playerStats.speed << endl;
			}
		}
	}
}