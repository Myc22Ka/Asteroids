#include "Pickup.h"
#include "WindowBox.h"

const map<double, Sprites> Pickup::boosters{
	{ 0.01, Sprites::HEART1UP },
	{ 0.075, Sprites::PICKUP_EXTRA_TIME },
	{ 0.1, Sprites::PICKUP_DRUNKMODE },
	{ 0.2, Sprites::PICKUP_FREEZE },
	{ 0.25, Sprites::PICKUP_TIMES_5 },
	{ 0.3, Sprites::PICKUP_SHIELD },
	{ 0.35, Sprites::PICKUP_EXTRA_SPEED },
	{ 0.4, Sprites::PICKUP_TIMES_2 },
	{ 0.5, Sprites::PICKUP_EXTRA_BULLET },
};

const vector<Sprites> Pickup::modifiers{ Sprites::PICKUP_EXTRA_BULLET, Sprites::PICKUP_EXTRA_SPEED, Sprites::PICKUP_EXTRA_TIME };
const vector<Sprites> Pickup::bulletTypes{ Sprites::PICKUP_HOMING, Sprites::PICKUP_PIERCING, Sprites::PICKUP_DOUBLESHOOT, Sprites::PICKUP_TRIPLESHOOT, Sprites::PICKUP_QUADSHOOT };

Pickup::Pickup(Vector2f position): Entity(position, 0, 64, Color::Cyan, SpriteInfo()),
lifeTime(5.0f)
{
	const auto dice = physics::rollDice();

	for (const auto& [prob, spriteType] : boosters) {
		if (dice < prob) {
			if (dice <= 0.5) spriteInfo = getSprite(spriteType);
			break;
		}
	}

	collected = getSprite(Sprites::COLLECTED);
	drawHitboxes(radius / 2);

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
}

Pickup::Pickup(Vector2f position, Sprites spriteType) : Entity(position, 0, 64, Color::Cyan, getSprite(spriteType)),
lifeTime(5.0f)
{
	spriteInfo = getSprite(spriteType);
	collected = getSprite(Sprites::COLLECTED);
	drawHitboxes(radius / 2);

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
}

void Pickup::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position));
	if (Game::hitboxesVisibility && spriteInfo.frames.size() != 0) window.draw(shape, transform);
}

void Pickup::update(float deltaTime)
{
	lifeTime -= deltaTime;
	collected.currentSpriteLifeTime -= deltaTime;

	if (spriteInfo.frames.size() != 0) collisionDetection();

	if (lifeTime <= 0) { 
		Game::removeEntity(this);
		return; 
	}

	if (Game::freeze.isEffectActive()) return;

	if(spriteInfo.frames.size() != 0) setSpriteFullCycle(deltaTime);
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
						Player::playerStats.critChance += 0.03;
					}

					Score::addScore(10);
					Player::playerStats.bulletDamage += 50.0f;
					SoundData::play(Sounds::PICKUP_EXTRA_BULLET);

					break;
				case Sprites::PICKUP_EXTRA_SPEED:
					if (Player::playerStats.speed < 500.0f) {
						Player::playerStats.speed += 15.0f;
						Player::playerStats.turnSpeed += 5.0f;
						Player::playerStats.bulletSpeed += 25.0f;
					}
					Score::addScore(20);
					SoundData::play(Sounds::PICKUP_EXTRA_SPEED);

					break;
				case Sprites::PICKUP_SHIELD:
					Score::addScore(50);
					Player::playerStats.shield.startEffect(15.0f + Player::playerStats.time);
					Player::playerStats.shield.getBar()->setMaxValue(Player::playerStats.shield.getEffectDuration());

					SoundData::play(Sounds::PICKUP_SHIELD);
					SoundData::sounds[Sounds::ACTIVE_SHIELD].setVolume(100);
					SoundData::playLooped(Sounds::ACTIVE_SHIELD);

					break;
				case Sprites::PICKUP_DRUNKMODE:
					Player::playerStats.drunkMode.startEffect(2.0f + Player::playerStats.time);
					Player::playerStats.drunkMode.getBar()->setMaxValue(Player::playerStats.drunkMode.getEffectDuration());

					Score::addScore(100);
					SoundData::play(Sounds::PICKUP_DRUNKMODE);

					break;
				case Sprites::PICKUP_PIERCING:
					if (!Player::playerStats.bulletType.piercing) Player::playerStats.bulletType.piercing = true;
					Score::addScore(1000);
					SoundData::play(Sounds::PICKUP_DRUNKMODE);

					break;
				case Sprites::PICKUP_HOMING:
					if (!Player::playerStats.bulletType.homing) Player::playerStats.bulletType.homing = true;
					Score::addScore(1000);
					SoundData::play(Sounds::PICKUP_EXTRA_BULLET);

					break;
				case Sprites::HEART1UP:
					if (Player::playerStats.lifes.size() <= 5) {
						Player::playerStats.lifes.push_back(Player::playerStats.lifes.back().offset + 20.0f);
						for (auto& life : Player::playerStats.lifes)
							life.setSpriteState(0);
					}
					SoundData::play(Sounds::HEART1UP);
					Score::addScore(200);

					break;
				case Sprites::PICKUP_FREEZE:
					SoundData::play(Sounds::FREEZE);
					Game::setGameState(FREZZE);
					Game::freeze.startEffect(physics::getRandomFloatValue(5.0f, 0.5f) + Player::playerStats.time);
					Score::addScore(50);

					break;
				case Sprites::PICKUP_EXTRA_TIME:
					SoundData::play(Sounds::PICKUP_EXTRA_TIME);
					if (Player::playerStats.time < 10.0f) Player::playerStats.time += 1.0f;
					Score::addScore(50);

					break;
				case Sprites::PICKUP_TIMES_2:
					SoundData::play(Sounds::PICKUP_TIMES_2);
					if (Player::playerStats.scoreTimes5.isEffectActive()) Player::playerStats.scoreTimes5.setEffectActive(false);
					Player::playerStats.scoreTimes2.startEffect(physics::getRandomFloatValue(10.0f, 0.5f) + Player::playerStats.time);
					Player::playerStats.scoreTimes2.getBar()->setMaxValue(Player::playerStats.scoreTimes2.getEffectDuration());
					Score::addScore(20);

					break;
				case Sprites::PICKUP_TIMES_5:
					SoundData::play(Sounds::PICKUP_TIMES_5);
					if (Player::playerStats.scoreTimes2.isEffectActive()) Player::playerStats.scoreTimes2.setEffectActive(false);
					Player::playerStats.scoreTimes5.startEffect(physics::getRandomFloatValue(10.0f, 0.5f) + Player::playerStats.time);
					Player::playerStats.scoreTimes5.getBar()->setMaxValue(Player::playerStats.scoreTimes5.getEffectDuration());
					Score::addScore(100);

					break;

				case Sprites::PICKUP_DOUBLESHOOT:
					SoundData::play(Sounds::PICKUP_DOUBLESHOOT);
					Player::playerStats.bulletAmount = 2;
					Score::addScore(1000);

					break;

				case Sprites::PICKUP_TRIPLESHOOT:
					SoundData::play(Sounds::PICKUP_TRIPLESHOOT);
					Player::playerStats.bulletAmount = 3;
					Score::addScore(1000);

					break;

				case Sprites::PICKUP_QUADSHOOT:
					SoundData::play(Sounds::PICKUP_QUADSHOOT);
					Player::playerStats.bulletAmount = 4;
					Score::addScore(1000);

					break;
				}
				Game::addEntity(new Explosion(this->position, this->size, collected));
			}
		}
	});
}

const Sprites Pickup::getRandomDrop(const map<double, Sprites>& group)
{
	const auto dice = physics::rollDice();

	for (const auto& [prob, spriteType] : group) {
		if (dice < prob) {
			if (dice <= 0.5) return spriteType;
		}
	}
	return Sprites();
}

const Sprites Pickup::getRandomFromGroup(const vector<Sprites>& group)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<size_t> dist(0, group.size() - 1);

	auto randomIndex = dist(gen);

	return group[randomIndex];
}