#include "Pickup.h"
#include "WindowBox.h"

Pickup::Pickup(Vector2f position, SpriteInfo s): Entity(position, 0, 64, Color::Cyan, s),
lifeTime(5)
{
	collected = getSprite(Sprites::COLLECTED);
	drawHitboxes(radius / 2);

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
				case Sprites::PICKUP_EXTRA_BULLET:
					if (Player::playerStats.shootOffset >= 0.11f) {
						Player::playerStats.shootOffset -= 0.01f;
						Player::playerStats.bulletSize += 3.0f;
					}

					Score::score += 10;
					Player::playerStats.bulletDamage += 50.0f;
					SoundData::play(Sounds::PICKUP_EXTRA_BULLET);
					break;
				case Sprites::PICKUP_EXTRA_SPEED:
					if (Player::playerStats.speed < 500.0f) {
						Player::playerStats.speed += 15.0f;
						Player::playerStats.turnSpeed += 5.0f;
						Player::playerStats.bulletSpeed += 25.0f;
					}
					Score::score += 20;
					SoundData::play(Sounds::PICKUP_EXTRA_SPEED);
					break;
				case Sprites::PICKUP_SHIELD:
					Score::score += 50;
					Player::playerStats.shield.startEffect(15.0f);

					SoundData::play(Sounds::PICKUP_SHIELD);
					break;
				case Sprites::PICKUP_DRUNKMODE:
					Player::playerStats.drunkMode.startEffect(15.0f);

					Score::score += 100;
					SoundData::play(Sounds::PICKUP_DRUNKMODE);
					break;
				case Sprites::PICKUP_PIERCING:
					if (!Player::playerStats.bulletType.piercing) Player::playerStats.bulletType.piercing = true;
					Score::score += 1000;
					SoundData::play(Sounds::PICKUP_DRUNKMODE);
					break;
				case Sprites::HEART1UP:
					if (Player::playerStats.lifes <= 5) {
						Player::playerStats.lifes += 1;
						WindowBox::playerHealthUIs.push_back(WindowBox::playerHealthUIs.back().offset + 20.0f);
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