#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "EntitiesList.h"
#include "Score.h"
#include <unordered_map>

export module WindowBox;

export class WindowBox
{
public:
	WindowBox();

	void displayWindow();
	static void gameOver();
	static void init();
	void begin();
	static bool hitboxesVisibility;

private:
	sf::RenderWindow window;
	static bool isGameOver;
	static float asteroidSpawnTime;
};
