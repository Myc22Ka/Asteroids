#include "Menu.h"
#include "WindowBox.h"

TextField Menu::menuText{ 128 };
vector<TextField> Menu::options{ { "New game", 24 }, { "Continue", 24 }, { "Highscore", 24 }, { "Exit", 24 } };
vector<TextField> Menu::navigation{ { "Confirm [Enter]", 8 }, { "Up [Up]", 8 }, { "Down [Down]", 8 }, { "Exit [ESC]", 8 } };
int Menu::selectedOption{ 0 };
Sprite Menu::background{};
Texture Menu::texture{};
bool Menu::isKeyPressed{ false };
bool Menu::confirm{ false };
float Menu::defaultPositionX{ 0.0f };

void Menu::init()
{
	menuText.setText("Asteroids++");
	menuText.setTextCenterX(FileMenager::screenData.padding * 4);

	FileMenager::highScore = FileMenager::sortMapByFloat(FileMenager::getDataFromFile("highscore.txt"));

	auto offset = 0.0f;
	for (auto& option : options) {
		Vector2f position = Vector2f(FileMenager::screenData.padding * 10, (WindowBox::getVideoMode().height >> 1) + offset);
		offset += 24 + 30.0f;
		option.setTextPosition(position);
	}

	float offsetX = 0.0f;

	for (auto& option : navigation)
	{
		offsetX += option.getText().getGlobalBounds().width / 2;
	}

	Vector2f position(WindowBox::getVideoMode().width - offsetX - FileMenager::screenData.padding, WindowBox::getVideoMode().height - FileMenager::screenData.padding - 12);

	for (auto& option : navigation)
	{
		option.setTextPosition(position);
		option.setSize(12);
		option.setColorText(Color(255, 255, 255, 150));

		position.x += option.getText().getGlobalBounds().width + 30.0f;
	}

	if (!texture.loadFromFile("./assets/menu.png"))
		cout << "Error: Cannot load background!" << endl;

	background.setTexture(texture);

	defaultPositionX = options[0].getText().getPosition().x;
}

void Menu::draw(RenderWindow& window) {
	window.draw(background);

	window.draw(menuText.getText());

	for (auto& option : options) {
		window.draw(option.getText());
	}

	for (auto& option : navigation)
	{
		window.draw(option.getText());
	}

	if (!confirm && Keyboard::isKeyPressed(Keyboard::Enter)) {
		confirm = true;

		switch (getSelectedOptionIndex()) {
		case 0:
			WindowBox::begin();
			break;
		case 1:
			WindowBox::begin();
			Game::setGameState(GAME_OVER);
			break;
		case 2:
			displayHighscoreTable(window);
			Game::setGameState(MENU_HIGHSCORE);
			break;
		case 3:
			SoundData::play(Sounds::GOODBYE);
			this_thread::sleep_for(chrono::milliseconds(1000));

			window.close();
			break;
		}
	}
}

void Menu::moveUp() {
	if (selectedOption > 0) {
		selectedOption--;
		return;
	}

	selectedOption = static_cast<int>(options.size()) - 1;
}

void Menu::moveDown() {
	if (selectedOption < options.size() - 1) {
		selectedOption++;
		return;
	}

	selectedOption = 0;
}

int Menu::getSelectedOptionIndex() {
	return selectedOption;
}

string Menu::getSelectedOption() {
	return options[selectedOption].getText().getString();
}

void Menu::navigator(const Event& event) {
	if (event.type == Event::KeyPressed && !isKeyPressed) {

		if (Game::getGameState() != MENU_HIGHSCORE) {
			if (event.key.code == Keyboard::Up) {
				moveUp();
				SoundData::play(Sounds::PING);
			}
			else if (event.key.code == Keyboard::Down) {
				moveDown();
				SoundData::play(Sounds::PING);
			}
		}

		isKeyPressed = true;
	}

	if (event.type == Event::KeyReleased) {
		isKeyPressed = false;
		confirm = false;
	}
}

void Menu::update(const float& deltaTime) {
	for (size_t i = 0; i < options.size(); ++i) {
		if (i == getSelectedOptionIndex()) {
			options[i].setColorText(sf::Color::Red);

			float x = min(options[i].getText().getPosition().x + 400.0f * deltaTime, defaultPositionX + 30.0f);

			options[i].setTextPosition(Vector2f(x, options[i].getText().getPosition().y));
		}
		else {
			options[i].setColorText(sf::Color::White);

			float x = max(options[i].getText().getPosition().x - 400.0f * deltaTime, defaultPositionX);

			options[i].setTextPosition(Vector2f(x, options[i].getText().getPosition().y));
		}
	}
}

void Menu::displayHighscoreTable(RenderWindow& window)
{
	TextField highscoreText{ 64 };
	highscoreText.setText("Highscore");
	highscoreText.setTextCenterX(FileMenager::screenData.padding);

	window.draw(background);

	window.draw(highscoreText.getText());

	for (auto& option : navigation)
	{
		window.draw(option.getText());
	}

	float offset = 0.0f;
	int counter = 1;

	for (auto& score : FileMenager::highScore)
	{
		TextField scoreText{ 16 };
		scoreText.setText(to_string(counter) + ". " + score.first + ": " + to_string(static_cast<size_t>(score.second)));
		scoreText.setTextPosition(Vector2f(WindowBox::getVideoMode().width / 1.5, FileMenager::screenData.padding + highscoreText.getText().getLocalBounds().height * 12 + offset));

		window.draw(scoreText.getText());

		offset += 30.0f;
		counter += 1;

		if (counter > 9) break;
	}

	if (Keyboard::isKeyPressed(Keyboard::Enter) && !confirm) {
		confirm = true;
		Game::setGameState(MENU);
	}
}