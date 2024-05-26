#pragma once
#ifndef MENULOADER_H
#define MENULOADER_H

#include "TextField.h"
#include "Page.h"

using namespace sf;
using namespace std;

class MenuLoader : public Page
{
public:
	MenuLoader();

	void run(const float& deltaTime, RenderWindow& window) override;
	void navigator(Event& e) override;

private:
	void init() override;

	void loadParticles();

	SpriteInfo loaderSprite;

	vector<pair<CircleShape, Vector2f>> loaderParticles;

	Effect launch;
};

#endif