#include "GameOver.h"

TextField GameOver::gameOverText{ 128 };
TextField GameOver::continueText{ 48 };

void GameOver::init()
{
	gameOverText.setText("Game Over!");
	continueText.setText("Press ENTER to continue ... ");
}
