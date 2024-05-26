#include "HighScoreTable.h"
#include "Menu.h"
#include "WindowBox.h"

HighScoreTable::HighScoreTable() : Page("menu"), highscoreText(64)
{
	init();
}

void HighScoreTable::init()
{
	Page::init();

	highscoreText.setText("Highscore");
	highscoreText.setTextCenterX(FileMenager::screenData.padding);
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

	if (Keyboard::isKeyPressed(Keyboard::Enter) && !Menu::confirm) {
		Menu::confirm = true;
		Game::setGameState(MENU);
	}
}
