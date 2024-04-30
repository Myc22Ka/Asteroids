#include "Pickup.h"
#include "WindowBox.h"

Pickup::Pickup(Vector2f position, SpriteInfo s): Entity(position, 0, 64, Color::Cyan, s),
lifeTime(5)
{
	collected = getSprite(Sprites::COLLECTED);
	drawHitboxes(static_cast<int>(size) >> 2);

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
}

void Pickup::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position));
	if (Game::hitboxesVisibility) window.draw(shape, transform);
}

void Pickup::update(float deltaTime)
{
	lifeTime -= deltaTime;
	collected.currentSpriteLifeTime -= deltaTime;

	collisionDetection();

	if (lifeTime <= 0) { 
		Game::removeEntity(this);
		return; 
	}

	if (Game::freeze.isEffectActive()) return;

	setSpriteFullCycle(deltaTime);
}

const EntityType Pickup::getEntityType()
{
	return EntityType::TYPE_PICKUP;
}

void Pickup::collisionDetection()
{
	Game::foreachEntity([&](Entity* entity) {
		if (entity->getEntityType() == EntityType::TYPE_PLAYER && entity != this) {
			Player* player = dynamic_cast<Player*>(entity);

			if (!player) return;

			if (physics::intersects(this->position, static_cast<float>(this->radius), player->position, player->radius) && static_cast<float>(lifeTime) > 0) {
				lifeTime = 0;

				switch (spriteInfo.spriteType)
				{
				case Sprites::PICKUP_1:
					if (Player::playerStats.shootOffset >= 0.11) Player::playerStats.shootOffset -= 0.01;
					Score::score += 10;
					SoundData::play(Sounds::PICKUP_1);
					break;
				case Sprites::PICKUP_2:
					Player::playerStats.bulletDamage += 50;
					Score::score += 20;
					SoundData::play(Sounds::PICKUP_2);
					break;
				case Sprites::PICKUP_3:
					if (Player::playerStats.bulletSize <= 50) Player::playerStats.bulletSize += 1;
					Score::score += 50;
					SoundData::play(Sounds::PICKUP_3);
					break;
				case Sprites::PICKUP_4:
					if (Player::playerStats.speed < 350) {
						Player::playerStats.speed += 10;
						Player::playerStats.turnSpeed += 5;
					}
					Score::score += 100;
					SoundData::play(Sounds::PICKUP_4);
					break;
				case Sprites::PICKUP_PIERCING:
					if (!Player::playerStats.bulletType.piercing) Player::playerStats.bulletType.piercing = true;
					Score::score += 1000;
					SoundData::play(Sounds::PICKUP_4);
					break;
				case Sprites::HEART1UP:
					if (Player::playerStats.lifes <= 5) {
						Player::playerStats.lifes += 1;
						WindowBox::playerHealthUIs.push_back(WindowBox::playerHealthUIs.back().offset + 20.0);
						for (auto& UI : WindowBox::playerHealthUIs)
							UI.setSpriteState(0);
					}
					SoundData::play(Sounds::HEART1UP);
					Score::score += 200;
					break;
				case Sprites::PICKUP_FREEZE:
					SoundData::play(Sounds::FREEZE);
					Game::freeze.startEffect(physics::getRandomFloatValue(10.0f, 0.5f));
					break;
				}
				Game::addEntity(new Explosion(this->position, this->size, collected));
			}
		}
	});
}