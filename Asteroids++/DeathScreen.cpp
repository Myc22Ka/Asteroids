#include "DeathScreen.h"
#include "WindowBox.h"

Effect DeathScreen::death{ 1.0f, false };
Effect DeathScreen::delay{ 0.5f, false };

DeathScreen::DeathScreen() : EventHandler(VertexArray(Quads, 16)), velocity(9000.0f) {
	initParticles();
}

void DeathScreen::update(float deltaTime) {
	delay.updateEffectDuration(deltaTime);

	if (delay.isEffectActive()) return;

	death.updateEffectDuration(deltaTime);

	for (size_t i = 0; i < 4; ++i) {
		particles[i * 4].position.x += velocity * deltaTime / 2 * death.getEffectDuration();
		particles[i * 4 + 1].position.x += velocity * deltaTime / 2 * death.getEffectDuration();
		particles[i * 4 + 2].position.x += velocity * deltaTime / 2 * death.getEffectDuration();
		particles[i * 4 + 3].position.x += velocity * deltaTime / 2 * death.getEffectDuration();
	}

	if (death.getEffectDuration() < 0) resetPosition();

}

const EntityType DeathScreen::getEntityType()
{
	return EntityType::TYPE_EVENT_DEATHSCREEN;
}

void DeathScreen::activateDeathScreen(const float& duration) {
	death.startEffect(duration);
	Game::setGameState(DEATH);
}

bool DeathScreen::isScreenOver() {
	return death.isEffectActive();
}

void DeathScreen::setDelay(const float& duration) {
	delay.startEffect(duration);
}

void DeathScreen::resetPosition() {
	float rectWidth = WindowBox::getVideoMode().width;
	float rectHeight = WindowBox::getVideoMode().height;

	for (size_t i = 0; i < 4; ++i) {
		float xOffset = i * 300.0f;

		particles[i * 4].position = sf::Vector2f(-xOffset, i * (rectHeight / 4));
		particles[i * 4 + 1].position = sf::Vector2f(-rectWidth * 2 - xOffset, i * (rectHeight / 4));
		particles[i * 4 + 2].position = sf::Vector2f(-rectWidth * 2 - xOffset, (i + 1) * (rectHeight / 4));
		particles[i * 4 + 3].position = sf::Vector2f(-xOffset, (i + 1) * (rectHeight / 4));
	}
}

void DeathScreen::init(const float& deltaTime, RenderWindow& window) {
	if (!death.isEffectActive() && Game::getGameState() == DEATH) {
		Game::setGameState(PLAYING);
		return;
	}
	if (!death.isEffectActive()) return;

	update(deltaTime);
	render(window);

	if(death.getEffectDuration() < 1.75f * 0.8 && Player::playerStats.lifes.size() == 0) Game::setGameState(GAME_OVER);
}

void DeathScreen::initParticles()
{
	resetPosition();

	for (int i = 0; i < particles.getVertexCount(); i++) {
		particles[i].color = Color::Black;
	}
}