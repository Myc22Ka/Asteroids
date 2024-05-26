#pragma once
#ifndef MENU_H
#define MENU_H

#include "TextField.h"
#include "Page.h"

using namespace sf;
using namespace std;

class Menu : public Page
{
public:
	Menu();

	void navigator(const Event& event);
	void run(const float& deltaTime, RenderWindow& window);

	static vector<TextField> navigation;
	static bool confirm;

private:
	void moveUp();
	void moveDown();

	void init();

	const int getSelectedOptionIndex() const;
	const string getSelectedOption() const;
	
	void draw(RenderWindow& window);

	TextField menuText;

	static vector<TextField> options;

	RectangleShape filter;

	int selectedOption;
	float defaultPositionX;

	bool isKeyPressed;
};

#endif