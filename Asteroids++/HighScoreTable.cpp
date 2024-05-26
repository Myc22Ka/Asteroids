#include "HighScoreTable.h"
#include "Menu.h"
#include "WindowBox.h"

HighScoreTable::HighScoreTable() : Page("menu"), highscoreText(64), isKeyPressed(false)
{
	init();
}

void HighScoreTable::init()
{
	Page::init();

	highscoreText.setText("Highscore");
	highscoreText.setTextCenterX(FileMenager::screenData.padding);

	FileMenager::highScore = FileMenager::sortMapByFloat(FileMenager::getDataFromFile("highscore.txt"));
}

void HighScoreTable::run(const float& deltaTime, RenderWindow& window)
{
	Page::run(deltaTime, window);


	window.draw(highscoreText.getText());

	for (auto& option : Menu::navigation)
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
}

void HighScoreTable::navigator(Event& e) {
	if (Keyboard::isKeyPressed(Keyboard::Enter) && !WindowBox::isKeyPressed) {
		Game::setGameState(MENU);

		WindowBox::isKeyPressed = true;
	}
}
