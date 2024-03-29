#include <SFML/Graphics.hpp>
#include "FileMenager.h"

export module WindowBox;

export class WindowBox : public FileMenager
{
public:
	WindowBox();

	void displayWindow();

private:
	sf::RenderWindow window;
};
