#include <SFML/Graphics.hpp>
#include "FileMenager.h"
#include "Entity.h"
#include "EntitiesList.h"

export module WindowBox;

export class WindowBox
{
public:
	WindowBox();

	void displayWindow();

private:
	sf::RenderWindow window;
};
