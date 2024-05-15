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
Effect Menu::visible{ 0.0f, false };
RectangleShape Menu::filter = RectangleShape();
Effect Menu::animateIn{ 0.0f, false };
Effect Menu::animateOut{ 0.0f, false };

void Menu::init()
{
	animateOut.startEffect(3.0f);
	filter.setSize({ static_cast<float>(WindowBox::getVideoMode().width), static_cast<float>(WindowBox::getVideoMode().height) });
	filter.setFillColor(Color::Black);

	visible.startEffect(1.0f);
	menuText.setText("Asteroids++");
	FloatRect textRect = menuText.getText().getLocalBounds();
	menuText.getText().setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	
	menuText.setTextPosition({ WindowBox::getVideoMode().width / 2.0f, 0.0f});

	FileMenager::highScore = FileMenager::sortMapByFloat(FileMenager::getDataFromFile("highscore.txt"));

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

	if (!texture.loadFromFile("./assets/menu.png"))
		cout << "Error: Cannot load background!" << endl;

	background.setTexture(texture);

	defaultPositionX = options[0].getText().getPosition().x;
}

void Menu::draw(RenderWindow& window) {
	window.draw(background);

	window.draw(menuText.getText(), Transform().translate(0.0f, -200.0f));

	float offset = 0.0f;
	for (auto& option : options) {
		window.draw(option.getText(), Transform().translate(-200.0f - offset, 0.0f));
		offset += 100.0f;
	}

	for (auto& option : navigation)
	{
		window.draw(option.getText());
	}

	window.draw(filter);

	if (animateOut.isEffectActive()) {
		thread t([&]() {
			Clock clock;
			float deltaTime = clock.restart().asSeconds();
			animateOut.updateEffectDuration(deltaTime);

			fadeOut(window, 3.0f);

			this_thread::sleep_for(chrono::milliseconds(30));
			});

		t.detach();
	}

	if (!confirm && Keyboard::isKeyPressed(Keyboard::Enter)) {
		confirm = true;
		animateIn.startEffect(1.0f);

		switch (getSelectedOptionIndex()) {
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
	animateIn.updateEffectDuration(deltaTime);
	animateOut.updateEffectDuration(deltaTime);

	float offset = 0.0f;

	if (visible.isEffectActive()) {
		visible.updateEffectDuration(deltaTime);

		float normalizedTime = visible.getEffectDuration() / 1.0f;
		float easingFactor = 1 - pow(1 - normalizedTime, 3); // Applying easeOutCubic
		float y = (FileMenager::screenData.padding * 8 + 200.0f) * (1 - easingFactor);

		menuText.getText().setPosition({ menuText.getText().getPosition().x, y});

		for (auto& option : options)
		{
			option.getText().setPosition({ (200.0f + offset) * (1 - easingFactor), option.getText().getPosition().y});
			offset += 100.0f;
		}
		return;
	}

	for (size_t i = 0; i < options.size(); ++i) {
		if (i == getSelectedOptionIndex()) {
			options[i].setColorText(sf::Color::Red);

			float x = min(options[i].getText().getPosition().x + 200.0f * deltaTime, defaultPositionX + offset + 260.0f);

			options[i].setTextPosition(Vector2f(x, options[i].getText().getPosition().y));
		}
		else {
			options[i].setColorText(sf::Color::White);

			float x = max(options[i].getText().getPosition().x - 200.0f * deltaTime, defaultPositionX + offset + 230.0f);

			options[i].setTextPosition(Vector2f(x, options[i].getText().getPosition().y));
		}

		offset += 100.0f;
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

void Menu::fadeIn(RenderWindow& window, const float& defaultTime)
{
	if (animateIn.isEffectActive()) {
		Color color = Color::Transparent;

		float opacity = 255.0f * (1 - animateIn.getEffectDuration() / defaultTime);

		color.a = static_cast<Uint8>(opacity);

		filter.setFillColor(color);
	}
	else {
		filter.setFillColor(Color::Black);
	}
}

void Menu::fadeOut(RenderWindow& window, const float& defaultTime)
{
	if (animateOut.isEffectActive()) {
		Color color = Color::Black;

		float opacity = 255.0f * (animateOut.getEffectDuration() / defaultTime);

		color.a = static_cast<Uint8>(opacity);

		filter.setFillColor(color);
	}
	else {
		filter.setFillColor(Color::Transparent);
	}
}