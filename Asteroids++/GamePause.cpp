#include "GamePause.h"
#include "WindowBox.h"

vector<string> GamePause::options{ "Resume", "Retry", "Quit" };
GamePause::GamePause() : EventHandler(VertexArray(Quads, 4)),
mainText(64),
selectedOption(0),
buttons({}),
prevGameState(GameState())
{
	vector<Sprites> icons = { Sprites::ICON_PLAY, Sprites::ICON_RETRY, Sprites::ICON_QUIT };

	float totalWidth = 100.0f;
	for (const auto& option : options)
	{
		totalWidth += 100.0f + 15.0f;
	}

	float startX = (WindowBox::getVideoMode().width - totalWidth) / 2.0f;

	float offset = 0.0f;
	for (size_t i = 0; i < options.size(); i++)
	{
		buttons.push_back({ icons[i], {options[i], 24}, Vector2f(startX + offset, 400.0f)});
		offset += 200.0f + 20.0f;
	}

	initParticles();

	mainText.setText("PAUSE");
	FloatRect textRect = mainText.getText().getLocalBounds();
	mainText.getText().setOrigin(textRect.left + textRect.width / 2.0f, textRect.top - textRect.height);

	mainText.setTextPosition({ WindowBox::getVideoMode().width / 2.0f, 0.0f });
}

void GamePause::update(float deltaTime)
{
	for (size_t i = 0; i < buttons.size(); ++i) {
		if (i == getSelectedOptionIndex()) {
			buttons[i].getText().setColorText({ 0, 128, 254 });
		}
		else {
			buttons[i].getText().setColorText(Color::White);
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

	update(deltaTime);
	render(window);

	mainText.draw(window);

	for (auto& button : buttons) button.draw(window);

}

void GamePause::initParticles()
{
	for (int i = 0; i < 1; i++) {
		particles[0].position = Vector2f(0.0f, 0.0f);
		particles[1].position = Vector2f(WindowBox::getVideoMode().width, 0.0f);
		particles[2].position = Vector2f(WindowBox::getVideoMode().width, WindowBox::getVideoMode().height);
		particles[3].position = Vector2f(0.0f, WindowBox::getVideoMode().height);

	}

	for (int i = 0; i < particles.getVertexCount(); i++) {
		particles[i].color = { 0, 0, 0, 150 };
	}
}

const int GamePause::getSelectedOptionIndex() const {
	return selectedOption;
}

void GamePause::moveLeft() {
	if (selectedOption > 0) {
		selectedOption--;
		return;
	}

	selectedOption = static_cast<int>(options.size()) - 1;
}

void GamePause::moveRight() {
	if (selectedOption < options.size() - 1) {
		selectedOption++;
		return;
	}

	selectedOption = 0;
}

void GamePause::navigator(Event& e)
{
	if (WindowBox::isKeyPressed) return;

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		moveRight();
		SoundData::play(Sounds::PING);

		WindowBox::isKeyPressed = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		moveLeft();
		SoundData::play(Sounds::PING);

		WindowBox::isKeyPressed = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		switch (selectedOption) {
		case 0:
			Game::setGameState(prevGameState);

			SoundData::recoverSound(Sounds::WIND);
			SoundData::recoverSound(Sounds::AMBIENT);

			break;
		case 1:
			SoundData::recoverSound(Sounds::AMBIENT);
			Score::clear();
			Game::clearEntities();
			Game::clearParticles();
			Game::level = 1;
			Player::playerStats.lifes.clear();

			WindowBox::begin();
			break;
		case 2:
			WindowBox::close();
			break;
		}

		WindowBox::isKeyPressed = true;
	}
}

void GamePause::setPrevGameState()
{
	prevGameState = Game::getGameState();
}
