#include "Menu.h"
#include "WindowBox.h"

vector<TextField> Menu::options{ { "New game", 24 }, { "Continue", 24 }, { "Highscore", 24 }, { "Exit", 24 } };
vector<TextField> Menu::navigation{ { "Confirm [Enter]", 8 }, { "Up [Up]", 8 }, { "Down [Down]", 8 }, { "Exit [ESC]", 8 } };
int Menu::selectedOption{ 0 };

Menu::Menu() : Page("menu"),
	menuText(128), 
	defaultPositionX(0.0f),  
	filter(RectangleShape())
{
	init();
}

void Menu::init()
{
	Page::init();

	menuText.setText("Asteroids++");
	FloatRect textRect = menuText.getText().getLocalBounds();
	menuText.getText().setOrigin(textRect.left + textRect.width / 2.0f, textRect.top - textRect.height);
	
	menuText.setTextPosition({ WindowBox::getVideoMode().width / 2.0f, 0.0f});

	if (navigation[0].getText().getPosition().x) return;

	auto offset = 0.0f;
	for (auto& option : options) {
		Vector2f position = Vector2f(0.0f, (WindowBox::getVideoMode().height >> 1) + offset);
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

	defaultPositionX = options[0].getText().getPosition().x;
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

const int Menu::getSelectedOptionIndex() const {
	return selectedOption;
}

const string Menu::getSelectedOption() const {
	return options[selectedOption].getText().getString();
}

void Menu::draw(RenderWindow& window) {
	for (auto& option : navigation) window.draw(option.getText());

	window.draw(menuText.getText());

	for (auto& option : options) window.draw(option.getText());
}

void Menu::navigator(Event& event)
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
			WindowBox::begin();
			break;
		case 1:
			WindowBox::begin();
			Game::setGameState(GAME_OVER);
			break;
		case 2:
			Game::setGameState(MENU_HIGHSCORE);
			break;
		case 3:
			WindowBox::close();
			break;
		}

		WindowBox::isKeyPressed = true;
	}
}

void Menu::run(const float& deltaTime, RenderWindow& window) {
	Page::run(deltaTime, window);

	for (size_t i = 0; i < options.size(); ++i) {
		if (i == getSelectedOptionIndex()) {
			options[i].setColorText(Color::Red);

			float x = min(options[i].getText().getPosition().x + 200.0f * deltaTime, defaultPositionX + 60.0f);

			options[i].setTextPosition(Vector2f(x, options[i].getText().getPosition().y));
		}
		else {
			options[i].setColorText(Color::White);

			float x = max(options[i].getText().getPosition().x - 200.0f * deltaTime, defaultPositionX + 30.0f);

			options[i].setTextPosition(Vector2f(x, options[i].getText().getPosition().y));
		}
	}

	draw(window);
}