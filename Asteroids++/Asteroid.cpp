#include "Asteroid.h"

constexpr double M_PI = 3.14159265358979323846;

Asteroid::Asteroid() : Entity(Vector2f(), getRandomAngle(), 0, getRandomValue<int>(FileMenager::enemiesData.asteroid_size), Color::Red),
health(100),
healthBar(size, 5, Color::Red, Color::Black, 100)
{
	spriteInfo = getSprite(Sprites::ASTEROID);
	direction = getRandomDirection();
	speed = getRandomValue<double>(FileMenager::enemiesData.asteroid_speed);
	position = getRandomPosition();

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

void Asteroid::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
	if(Game::hitboxesVisibility) window.draw(shape, transform);
	healthBar.draw(window);
}

void Asteroid::update(float deltaTime) {
	angle += FileMenager::enemiesData.asteroid_spin * deltaTime;
	position += Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);
	spriteInfo.spriteLifeTime -= deltaTime;

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
	}

	healthBar.updateBar(Vector2f{ position.x - (float)radius, position.y + (float)radius });
	healthBar.setCurrentValue(health);

	//if (spriteInfo.spriteLifeTime <= 0) {
	//	spriteInfo.spriteLifeTime = FileMenager::playerData.sprite_cycle_time;
 	//	spriteState = (spriteState + 1) % spriteInfo.frames.size();
	//	updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteState);
	//}

	collisionDetection();
}

const CircleShape& Asteroid::getVertexShape() const
{
	return shape;
}

const EntityType Asteroid::getEntityType()
{
	return EntityType::TYPE_ASTEROID;
}

void Asteroid::collisionDetection()
{
	for (const auto& entity : Game::entities) {
		if (entity->getEntityType() == EntityType::TYPE_ASTEROID && entity != this) {
			Asteroid* otherAsteroid = dynamic_cast<Asteroid*>(entity);

			if(otherAsteroid)
				if (physics::intersects(this->position, radius, otherAsteroid->position, otherAsteroid->radius)) {
					const Vector2f normal = physics::normalize(this->position - otherAsteroid->position);

					// Calculate overlap distance
					const float overlap = (this->size + otherAsteroid->size) - physics::distance(this->position, otherAsteroid->position);

					// Separate the asteroids along the collision normal to resolve overlap
					const Vector2f separationVector = normal * overlap * 0.01f;
					this->position += separationVector;
					otherAsteroid->position -= separationVector;

					// Calculate relative velocity along the normal direction
					const Vector2f relativeVelocity = this->speed * physics::normalize(this->direction) - otherAsteroid->speed * physics::normalize(otherAsteroid->direction);
					const float velAlongNormal = physics::dotProduct(relativeVelocity, normal);

					// Calculate total mass
					const float totalMass = this->size + otherAsteroid->size;

					// Calculate the maximum change in direction allowed
					const float maxChangeFactor = 0.7f;
					const float maxChangeMagnitude = maxChangeFactor * velAlongNormal / totalMass;

					// Calculate the change in direction based on momentum conservation, limited by the maximum change
					const Vector2f changeInDirection = min(maxChangeMagnitude, abs(velAlongNormal)) * normal;

					// Apply change in direction to each asteroid
					this->direction -= changeInDirection;
					otherAsteroid->direction += changeInDirection;
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

const float Asteroid::getRandomAngle()
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
	uniform_real_distribution<double> dist(0.5 * based, 1.5 * based);

	return static_cast<T>(dist(gen));
}
