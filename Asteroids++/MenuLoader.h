#pragma once
#ifndef MENULOADER_H
#define MENULOADER_H

#include "TextField.h"
#include "Player.h"

using namespace sf;
using namespace std;

class MenuLoader : public SpriteData
{
public:

	void init();
	void run(const float& deltaTime, RenderWindow& window);

private:
	void loadParticles();

	SpriteInfo loaderSprite;
	Sprite loader;
	Texture loaderTexture;

	vector<pair<CircleShape, Vector2f>> loaderParticles;

	Effect launch;
};

#endif