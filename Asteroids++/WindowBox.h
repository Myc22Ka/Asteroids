#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "Game.h"
#include "Score.h"
#include "SpriteData.h"
#include <unordered_map>
#include "Wind.h"
#include "Effect.h"
#include "TextField.h"

class WindowBox : public SpriteData
{
public:
	WindowBox();

	static VideoMode getVideoMode();
	void displayWindow();
	void begin();
private:

	void engine(Wind& wind, const float& deltaTime);

	void launchGame(const float& deltaTime);

	void initSprite(Sprite& sprite, const string filename, Texture& texture);
	void displayMenu();
	void updateWindow(const float& deltaTime);
	void renderUI();

	void loadParticles();

	static VideoMode videoMode;
	static TextField fps;
	Effect fpsDelay;

	Sprite background;
	Texture backgroundTexture;

	SpriteInfo loaderSprite;
	Sprite loader;
	Texture loaderTexture;

	vector<pair<CircleShape, Vector2f>> loaderParticles;

	Effect launch;

	RenderWindow window;

	bool keyPressed;
};
