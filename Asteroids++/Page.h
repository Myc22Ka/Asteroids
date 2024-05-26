#pragma once
#ifndef PAGE_H
#define PAGE_H

#include "TextField.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Page
{
public:
	Page(string backgroundname);

	virtual void init();
	virtual void run(const float& deltaTime, RenderWindow& window);

	Color getBackgroundColor();
	void setBackgroundColor(const Color& newColor);

private:
	string backgroundname;

	Sprite background;
	Texture texture;
};

#endif