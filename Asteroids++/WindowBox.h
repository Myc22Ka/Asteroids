#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "Game.h"
#include "DeathScreen.h"

class WindowBox
{
public:
	WindowBox();

	static VideoMode getVideoMode();
	void displayWindow();
	static void begin();

	static void close();

	static bool isKeyPressed;
private:
	int counter;

	static VideoMode videoMode;
	static DeathScreen* deathScreen;

	static RenderWindow window;
};
