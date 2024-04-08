#include <SFML/Graphics.hpp>
#include "FileMenager.h"
#include "EntitiesList.h"
#include "Score.h"

export module WindowBox;

export class WindowBox
{
public:
	WindowBox();

	void displayWindow();

private:
	sf::RenderWindow window;
};
