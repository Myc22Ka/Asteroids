#include "Asteroid.h"
#include "Score.h"

constexpr double M_PI = 3.14159265358979323846;

Asteroid::Asteroid(double health, SpriteInfo spriteInfo) :
	Entity(getRandomPosition(), getRandomAngle(), getRandomValue<int>(FileMenager::enemiesData.asteroid_size), Color::Red, spriteInfo),
	health(health + floor(Score::score >> 9) * health),
	healthBar(size, 5, Color::Red, Color::Black, health + floor(Score::score >> 9) * health),
	direction(getRandomDirection()),
	speed(getRandomValue<double>(FileMenager::enemiesData.asteroid_speed))
{
}

void Asteroid::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(static_cast<float>(angle)));
	if(Game::hitboxesVisibility) window.draw(shape, transform);
	healthBar.draw(window);
}

void Asteroid::update(float deltaTime) {
	/*angle += FileMenager::enemiesData.asteroid_spin * deltaTime;
	position += Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);

	if (position.x < radius) {
		direction.x = abs(direction.x);
	}
	else if (position.x > FileMenager::screenData.size_width - radius) {
		direction.x = -abs(direction.x);
	}

	if (position.y < radius) {
		direction.y = abs(direction.y);
	}
	else if (position.y > FileMenager::screenData.size_height - radius) {
		direction.y = -abs(direction.y);
	}*/

	healthBar.updateBar(Vector2f{ position.x - (float)radius, position.y + (float)radius });
	healthBar.setCurrentValue(health);

	setSpriteFullCycle(deltaTime);

	collisionDetection();
}

void Asteroid::collisionDetection()
{
	for (const auto& entity : Game::entities) {
		if ((entity->getEntityType() == EntityType::TYPE_ENEMY_MULTI_ASTEROID || entity->getEntityType() == EntityType::TYPE_ENEMY_SINGLE_ASTEROID) 
			&& entity != this) {
			Asteroid* otherAsteroid = dynamic_cast<Asteroid*>(entity);

			if (!otherAsteroid) return;

				if (physics::intersects(this->position, radius, otherAsteroid->position, otherAsteroid->radius)) {
					const auto bounceDirection = physics::bounceDirection(this, otherAsteroid, 0.01f);

					this->position += bounceDirection.second;
					otherAsteroid->position -= bounceDirection.second;

					this->direction -= bounceDirection.first;
					otherAsteroid->direction += bounceDirection.first;
			}
		}
	}
}

const Vector2f Asteroid::getRandomPosition() const
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> xAxis(radius, FileMenager::screenData.size_width - radius);
	uniform_real_distribution<double> yAxis(radius, FileMenager::screenData.size_height - radius);

	auto player = Game::doesEntityExist(EntityType::TYPE_PLAYER);

	if (player) {
		Vector2f randomPosition;

		do {
			randomPosition = Vector2f(xAxis(gen), yAxis(gen));
		} while (physics::intersects(randomPosition, radius, player->position, player->size << 1));

		return randomPosition;
	}
	else {
		return Vector2f(); 
	}
}

const double Asteroid::getRandomAngle()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist(0.0, 360.0);

	return dist(gen);
}

const Vector2f Asteroid::getRandomDirection()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist(0.0, 2.0f * M_PI);

	double angle = dist(gen);
	return Vector2f(cos(angle), sin(angle));
}

template<typename T>
inline const T Asteroid::getRandomValue(const T& base)
{
	const double based = base;
		
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist(0.75 * based, 1.25 * based);

	return static_cast<T>(dist(gen));
}
