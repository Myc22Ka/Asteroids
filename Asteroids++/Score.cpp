#include "Score.h"
#include "WindowBox.h"

size_t Score::score{ 0 };
TextField Score::scoreText{ 24 };

unordered_map<Sprites, int> Score::scoreTable{
	{ Sprites::PICKUP_EXTRA_BULLET, 10 },
	{ Sprites::PICKUP_EXTRA_SPEED, 20 },
	{ Sprites::PICKUP_SHIELD, 50 },
	{ Sprites::PICKUP_DRUNKMODE, 100 },
	{ Sprites::PICKUP_PIERCING, 250 },
	{ Sprites::PICKUP_HOMING, 500 },
	{ Sprites::PICKUP_POISON, 250 },
	{ Sprites::HEART1UP, 200 },
	{ Sprites::PICKUP_FREEZE, 50 },
	{ Sprites::PICKUP_EXTRA_TIME, 50 },
	{ Sprites::PICKUP_TIMES_2, 20 },
	{ Sprites::PICKUP_TIMES_5, 100 },
	{ Sprites::PICKUP_DOUBLESHOOT, 200 },
	{ Sprites::PICKUP_TRIPLESHOOT, 300 },
	{ Sprites::PICKUP_QUADSHOOT, 400 }
};

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

void Score::addScore(Sprites& sprite) {
	addScore(scoreTable[sprite]);
}