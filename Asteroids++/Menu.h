#pragma once
#ifndef MENU_H
#define MENU_H

#include "TextField.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Menu
{
public:
	static void init();
	static void draw(RenderWindow& window);

	static void moveUp();
	static void moveDown();
	static int getSelectedOptionIndex();
	static string getSelectedOption();

	static void navigator(const Event& event);
	static void update(const float& deltaTime);

private:
	static Texture texture;
	static Sprite background;
	static TextField menuText;
	static vector<TextField> options;
	static int selectedOption;
	static float defaultPositionX;

	static bool isKeyPressed;
};

#endif