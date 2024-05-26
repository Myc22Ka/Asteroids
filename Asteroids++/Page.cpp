#include "Page.h"


Page::Page(string backgroundname) : backgroundname(backgroundname)
{
	init();
}

void Page::init()
{
	if (!texture.loadFromFile("./assets/" + backgroundname + ".png"))
		cout << "Error: Cannot load background!" << endl;

	background.setTexture(texture);
}

void Page::run(const float& deltaTime, RenderWindow& window)
{
	window.draw(background);
}

Color Page::getBackgroundColor()
{
	return background.getColor();
}

void Page::setBackgroundColor(const Color& newColor)
{
	background.setColor(newColor);
}
