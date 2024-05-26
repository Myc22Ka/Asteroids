#pragma once
#ifndef GAMEPAUSE_H
#define GAMEPAUSE_H

#include "EventHandler.h"
#include "TextField.h"

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

	void moveUp();
	void moveDown();
	const int getSelectedOptionIndex() const;

	TextField mainText;
	static vector<TextField> options;

	int selectedOption;
};

#endif