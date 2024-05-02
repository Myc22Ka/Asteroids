#include "Wind.h"
#include "WindowBox.h"

Wind::Wind() : Entity(getRandomPosition(), 0, 0, Color::Yellow, SpriteInfo()), 
windSpeed(200.0f),
wind(3.0f, false),  
windLevel(3.0f), 
lineWidth(30.0f), 
lineHeight(0.8f), 
velocity(physics::getRandomDirection())
{
	fullWindDuration = wind.getEffectDuration();
	particles.setPrimitiveType(Lines);
	particles.resize(400);

	for (size_t i = 0; i < particles.getVertexCount(); i += 2) {
		Vector2f position = getRandomPosition();
		particles[i].position = position;
		particles[i].color = Color::White;
		particles[i + 1].position = position + velocity * lineHeight;
		particles[i + 1].color = Color::White;
	}
}

const Vector2f Wind::getRandomPosition() const 
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> xAxis(0.0f, float(WindowBox::getVideoMode().width));
	uniform_real_distribution<float> yAxis(0.0f, float(WindowBox::getVideoMode().height));

	return Vector2f(xAxis(gen), yAxis(gen));
}

void Wind::render(RenderWindow& window)
{
	window.draw(particles);
}

void Wind::update(float deltaTime)
{
	if (Game::freeze.isEffectActive()) return;

	for (size_t i = 0; i < particles.getVertexCount() - 1; i += 2)
	{
		particles[i].position += velocity * windSpeed * deltaTime;
		particles[i + 1].position += velocity * windSpeed * deltaTime;
		wrapLine(particles[i], particles[i + 1]);
	}

	if (!wind.isEffectActive()) return;

	wind.updateEffectDuration(deltaTime);

	if (wind.getEffectDuration() < 0) {
		stopWind();
		return;
	}

	for (size_t i = 0; i < particles.getVertexCount() - 1; i += 2)
	{
		particles[i].position += velocity * windSpeed * windLevel * deltaTime + (wind.getEffectDuration() > fullWindDuration - lineHeight ? velocity : Vector2f(0, 0));
		particles[i + 1].position += velocity * windSpeed * windLevel * deltaTime + (wind.getEffectDuration() < lineHeight ? velocity : Vector2f(0, 0));
		wrapLine(particles[i], particles[i + 1]);
	}

	for (auto& entity : Game::getEntities())
	{
		if (!entity || !entity->isActive() || entity->getEntityType() != TYPE_PLAYER) continue;

		if (entity->position.x < entity->radius || entity->position.x >= WindowBox::getVideoMode().width - entity->radius ||
			entity->position.y < entity->radius || entity->position.y >= WindowBox::getVideoMode().height - entity->radius)
			continue;

		entity->position += velocity * windLevel;
	}
}

void Wind::stopWind() {
	wind.setEffectActive(false);
	windSpeed = 200.0f;
	SoundData::stop(Sounds::WIND);

	thread windThread([this]() {resetParticlePositions(); });

	windThread.detach();

	return;
}

void Wind::resetParticlePositions() {
	for (size_t i = 0; i < particles.getVertexCount() - 1; i += 2) {
		Vector2f diff = particles[i + 1].position - particles[i].position;

		float currentDistance = physics::distance(particles[i].position, particles[i + 1].position);

		if (currentDistance != 0) {
			Vector2f normalizedDiff = diff / currentDistance;

			Vector2f newPosition = particles[i].position + normalizedDiff;

			particles[i + 1].position = newPosition;
		}
		else {
			particles[i + 1].position = particles[i].position;
		}

		wrapLine(particles[i], particles[i + 1]);
	}
}

void Wind::wrapLine(Vertex& vertex1, Vertex& vertex2) const {
	Vector2f windowSize(float(WindowBox::getVideoMode().width), float(WindowBox::getVideoMode().height));

	// Left boundary
	if (vertex1.position.x < 0 || vertex2.position.x < 0) {
		vertex1.position.x += windowSize.x;
		vertex2.position.x += windowSize.x;
	}

	// Right boundary
	if (vertex1.position.x >= windowSize.x || vertex2.position.x >= windowSize.x) {
		vertex1.position.x -= windowSize.x;
		vertex2.position.x -= windowSize.x;
	}

	// Top boundary
	if (vertex1.position.y < 0 || vertex2.position.y < 0) {
		vertex1.position.y += windowSize.y;
		vertex2.position.y += windowSize.y;
	}

	// Bottom boundary
	if (vertex1.position.y >= windowSize.y || vertex2.position.y >= windowSize.y) {
		vertex1.position.y -= windowSize.y;
		vertex2.position.y -= windowSize.y;
	}
}

void Wind::activateWind(const float& duration, const float& windLevel, const Vector2f& velocity) {
	if (physics::rollDice(0.0005) && !wind.isEffectActive() && SoundData::sounds[Sounds::WIND].getVolume() == 100 && !Game::freeze.isEffectActive()) {

	wind.startEffect(duration);
	fullWindDuration = duration;
	windSpeed = windLevel * 100.0f;
	this->windLevel = windLevel;
	this->velocity = velocity;

	SoundData::play(Sounds::WIND);
	}
}

const EntityType Wind::getEntityType()
{
	return EntityType::TYPE_EVENT_WIND;
}

void Wind::collisionDetection() {}