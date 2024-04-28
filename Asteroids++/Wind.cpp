#include "Wind.h"

Wind::Wind() : Entity(getRandomPosition(), 0, Asteroid::getRandomValue(64), Color::Yellow, SpriteInfo()), windSpeed(200.0f), windDirection(0.0f), windActive(false), windDuration(3.0f), windDelay(0.1f), windLevel(3.0f), lineWidth(30.0f), lineHeight(4), wasWindActive(true)
{
	particles.setPrimitiveType(Quads);
	particles.resize(800);

	for (size_t i = 0; i < particles.getVertexCount(); i += 4) {
		Vector2f position = getRandomPosition();
		particles[i].position = position;
		particles[i].color = Color::White;
		particles[i + 1].position = position + Vector2f(lineHeight, 0);
		particles[i + 1].color = Color::White;
		particles[i + 2].position = position + Vector2f(lineHeight, lineHeight);
		particles[i + 2].color = Color::White;
		particles[i + 3].position = position + Vector2f(0, lineHeight);
		particles[i + 3].color = Color::White;
	}
}

const Vector2f Wind::getRandomPosition() const 
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> xAxis(radius, -FileMenager::screenData.size_width - radius);
	uniform_real_distribution<double> yAxis(radius, FileMenager::screenData.size_height - radius);

	return Vector2f(xAxis(gen), yAxis(gen));
}

void Wind::render(RenderWindow& window)
{
	window.draw(particles);
}

void Wind::update(float deltaTime)
{
	windDuration -= deltaTime;

	if (!windActive) {
		if (!wasWindActive) {
			windDelay -= deltaTime;
			wasWindActive = true;
			cout << "hi" << endl;
			resetParticlePositions();
		}
		return;
	}

	if (windDuration <= 0) {
		windActive = false;
		wasWindActive = false;
		windDelay = 0.1f;
		cout << "Wind duration ended. Setting wasWindActive to true." << endl;
		return;
	}

	windDelay -= deltaTime;

	Vector2f velocity = Vector2f(windSpeed * cos(windDirection), windSpeed * sin(windDirection));

	if (windDelay <= 0) {
		float interpolationFactor = min(1.0f - (windDelay / 0.01f), lineWidth);

		for (size_t i = 0; i < particles.getVertexCount(); i += 4) {
			particles[i + 1].position = particles[i].position + Vector2f(interpolationFactor, 0);
			particles[i + 2].position = particles[i].position + Vector2f(interpolationFactor, lineHeight);
			particles[i + 3].position = particles[i].position + Vector2f(0, lineHeight);
			wrapQuad(particles[i], particles[i + 1], particles[i + 2], particles[i + 3]);
		}
	}

	for (size_t i = 0; i < particles.getVertexCount(); i += 4) {
		particles[i].position += velocity * (deltaTime * windLevel);
		particles[i + 1].position += velocity * (deltaTime * windLevel);
		particles[i + 2].position += velocity * (deltaTime * windLevel);
		particles[i + 3].position += velocity * (deltaTime * windLevel);
		wrapQuad(particles[i], particles[i + 1], particles[i + 2], particles[i + 3]);
	}

	wasWindActive = true;
}

void Wind::resetParticlePositions() {
	float interpolationFactor = min(1.0f - (windDelay / 0.01f), lineHeight);

	for (size_t i = 0; i < particles.getVertexCount(); i += 4) {
		particles[i + 1].position = particles[i].position + Vector2f(interpolationFactor, 0);
		particles[i + 2].position = particles[i].position + Vector2f(interpolationFactor, lineHeight);
		particles[i + 3].position = particles[i].position + Vector2f(0, lineHeight);
		wrapQuad(particles[i], particles[i + 1], particles[i + 2], particles[i + 3]);
	}
}

void Wind::wrapQuad(Vertex& vertex1, Vertex& vertex2, Vertex& vertex3, Vertex& vertex4) const {
	Vector2f windowSize(FileMenager::screenData.size_width, FileMenager::screenData.size_height);

	const int offset = -(int)lineWidth << 1;

	if (vertex1.position.x < offset || vertex2.position.x < offset || vertex3.position.x < offset || vertex4.position.x < offset) {
		vertex1.position.x += windowSize.x;
		vertex2.position.x += windowSize.x;
		vertex3.position.x += windowSize.x;
		vertex4.position.x += windowSize.x;
	}

	if (vertex1.position.x >= windowSize.x || vertex2.position.x >= windowSize.x || vertex3.position.x >= windowSize.x || vertex4.position.x >= windowSize.x) {
		float wrapDistance = windowSize.x + lineWidth;
		vertex1.position.x -= wrapDistance;
		vertex2.position.x -= wrapDistance;
		vertex3.position.x -= wrapDistance;
		vertex4.position.x -= wrapDistance;
	}
}

void Wind::activateWind(float duration, float speed, float direction) {
	windDuration = duration;
	windSpeed = speed;
	windDirection = direction;
	windActive = true;
}

const EntityType Wind::getEntityType()
{
	return EntityType::TYPE_EVENT_WIND;
}

void Wind::collisionDetection() {}