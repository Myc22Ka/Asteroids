#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "Game.h"
#include "Score.h"
#include "SpriteData.h"
#include <unordered_map>


class WindowBox
{
public:
	WindowBox();

	void displayWindow();
	static void init();
	void begin();

private:
	RenderWindow window;
	static double asteroidSpawnTime;
	static double heartAnimationTimer;
};
