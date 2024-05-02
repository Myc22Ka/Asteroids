#pragma once
#ifndef SCORE_H
#define SCORE_H

#include "TextField.h"
#include "Player.h"
#include <string>

using namespace sf;
using namespace std;

class Score
{
public:
	static TextField scoreText;

	static void init();

	static size_t getScore();
	static string getScoreString();
	static void addScore(const size_t& value);
private:
	static size_t score;
};

#endif 
