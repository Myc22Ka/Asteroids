#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "Game.h"
#include "Score.h"
#include "SpriteData.h"
#include <unordered_map>

export module WindowBox;

export class WindowBox
{
public:
	WindowBox();

	void displayWindow();
	static void init();
	void begin();

private:
	RenderWindow window;
	static float asteroidSpawnTime;
};
