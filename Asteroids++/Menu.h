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

	void navigator(Event& event) override;
	void run(const float& deltaTime, RenderWindow& window) override;

	static vector<TextField> navigation;
private:
	void moveUp();
	void moveDown();

	void init() override;

	const int getSelectedOptionIndex() const;
	const string getSelectedOption() const;
	
	void draw(RenderWindow& window);

	TextField menuText;

	static vector<TextField> options;

	RectangleShape filter;

	static int selectedOption;
	float defaultPositionX;
};

#endif