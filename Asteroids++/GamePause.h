#pragma once
#ifndef GAMEPAUSE_H
#define GAMEPAUSE_H

#include "EventHandler.h"
#include "TextField.h"
#include "Button.h"

using namespace sf;
using namespace std;

class GamePause : public EventHandler
{
public:
	GamePause();

	void update(float deltaTime) override;
	const EntityType getEntityType() override;
	void init(const float& deltaTime, RenderWindow& window) override;
	void initParticles() override;

	void navigator(Event& e);
private:

	void moveRight();
	void moveLeft();
	const int getSelectedOptionIndex() const;

	TextField mainText;
	static vector<string> options;
	vector<Button> buttons;

	int selectedOption;
};

#endif