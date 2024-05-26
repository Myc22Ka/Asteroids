#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "Game.h"
#include "GameOver.h"
#include "Score.h"
#include "SpriteData.h"
#include <unordered_map>
#include "Wind.h"
#include "Effect.h"
#include "TextField.h"
#include "MenuLoader.h"
#include "HighScoreTable.h"
#include "Menu.h"

class WindowBox
{
public:
	WindowBox();

	static VideoMode getVideoMode();
	void displayWindow();
	static void begin();
private:

	void handleKeyPress(Keyboard::Key keyCode, Wind& wind);

	void engine(Wind& wind, MenuLoader& loader, GameOver& gameOver, HighScoreTable& highScoreTable, Menu& menu, const float& deltaTime);

	void updateWindow(const float& deltaTime);
	void renderUI();

	static VideoMode videoMode;
	static TextField fps;
	Effect fpsDelay;

	Sprite background;
	Texture backgroundTexture;

	RenderWindow window;
};
