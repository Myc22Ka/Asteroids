#include <SFML/Graphics.hpp>

export module WindowBox;

export class WindowBox
{
public:
	WindowBox();

	void displayWindow();

private:
	sf::RenderWindow window;
};
