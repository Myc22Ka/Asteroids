#include "GamePause.h"
#include "WindowBox.h"

vector<TextField> GamePause::options{ { "Resume", 24 }, { "Retry", 24 }, { "Abandon Ship", 24 } };

GamePause::GamePause() : EventHandler(VertexArray(Quads, 4)),
mainText(64),
selectedOption(0)
{
	initParticles();
}

void GamePause::update(float deltaTime)
{
	for (size_t i = 0; i < options.size(); ++i) {
		if (i == getSelectedOptionIndex()) {
			options[i].setColorText(Color::Red);
		}
		else {
			options[i].setColorText(Color::White);
		}
	}
}

const EntityType GamePause::getEntityType()
{
	return EntityType();
}

void GamePause::init(const float& deltaTime, RenderWindow& window)
{
	if (Game::getGameState() != PAUSED) return;

	mainText.setText("PAUSE");
	FloatRect textRect = mainText.getText().getLocalBounds();
	mainText.getText().setOrigin(textRect.left + textRect.width / 2.0f, textRect.top - textRect.height);

	mainText.setTextPosition({ WindowBox::getVideoMode().width / 2.0f, 0.0f });

	auto offset = 0.0f;
	for (auto& option : options) {
		Vector2f position = Vector2f(0.0f, (WindowBox::getVideoMode().height >> 1) + offset);
		offset += 24 + 30.0f;
		option.setTextPosition(position);
	}

	update(deltaTime);
	render(window);

	window.draw(mainText.getText());

	for (auto& option : options) window.draw(option.getText());

}

void GamePause::initParticles()
{
	for (int i = 0; i < 1; i++) {
		particles[0].position = Vector2f(10.0f, 10.0f);
		particles[1].position = Vector2f(WindowBox::getVideoMode().width - 20.0f, 10.0f);
		particles[2].position = Vector2f(WindowBox::getVideoMode().width - 20.0f, WindowBox::getVideoMode().height - 20.0f);
		particles[3].position = Vector2f(10.0f, WindowBox::getVideoMode().height - 20.0f);

	}

	for (int i = 0; i < particles.getVertexCount(); i++) {
		particles[i].color = { 0, 0, 0, 150 };
	}
}

const int GamePause::getSelectedOptionIndex() const {
	return selectedOption;
}

void GamePause::moveUp() {
	if (selectedOption > 0) {
		selectedOption--;
		return;
	}

	selectedOption = static_cast<int>(options.size()) - 1;
}

void GamePause::moveDown() {
	if (selectedOption < options.size() - 1) {
		selectedOption++;
		return;
	}

	selectedOption = 0;
}

void GamePause::navigator(Event& e)
{
	if (WindowBox::isKeyPressed) return;

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		moveUp();
		SoundData::play(Sounds::PING);

		WindowBox::isKeyPressed = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		moveDown();
		SoundData::play(Sounds::PING);

		WindowBox::isKeyPressed = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		switch (selectedOption) {
		case 0:
			Game::setGameState(PLAYING);
			SoundData::recoverSound(Sounds::AMBIENT);
			break;
		case 1:
			Game::setGameState(GAME_OVER);
			break;
		case 2:
			Game::setGameState(MENU);
			break;
		}

		WindowBox::isKeyPressed = true;
	}
}
