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

private:
	sf::RenderWindow window;
};
