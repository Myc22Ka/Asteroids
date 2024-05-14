#include "Score.h"
#include "WindowBox.h"

size_t Score::score{ 0 };
TextField Score::scoreText{ 24 };

void Score::init() {
	scoreText.setTextCenterX(FileMenager::screenData.padding);
	scoreText.setText(getScoreString());
}

size_t Score::getScore() {
	return score;
}

string Score::getScoreString()
{
	return to_string(score);
}

void Score::clear() {
	score = 0;
}

void Score::addScore(const size_t& value)
{
	score += (value * (Player::playerStats.scoreTimes2.isEffectActive() ? 2 : Player::playerStats.scoreTimes5.isEffectActive() ? 5 : 1));
}
