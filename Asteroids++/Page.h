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
	Page();

	virtual void init();
	virtual void run(const float& deltaTime, RenderWindow& window);
	virtual void navigator(Event& e) = 0;

	Color getBackgroundColor();
	void setBackgroundColor(const Color& newColor);

private:
	string backgroundname;

	Sprite background;
	Texture texture;
};

#endif