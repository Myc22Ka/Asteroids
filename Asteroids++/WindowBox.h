#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "Game.h"
#include "Score.h"
#include "SpriteData.h"
#include <unordered_map>
#include "PlayerHealthUI.h"
#include "Wind.h"
#include "Effect.h"

class WindowBox : public SpriteData
{
public:
	WindowBox();

	static VideoMode getVideoMode();
	void displayWindow();
	void begin();

	static vector<PlayerHealthUI> playerHealthUIs;
private:

	void engine(Wind& wind, const float& deltaTime);

	void launchGame(const float& deltaTime);

	void initSprite(Sprite& sprite, const string filename, Texture& texture);
	void displayMenu();
	void updateWindow(const float& deltaTime);
	void renderUI();
	void spawnEnemy(const float& deltaTime);
	void updateWind(Wind& wind, const float& deltaTime);

	static VideoMode videoMode;

	Sprite background;
	Texture backgroundTexture;

	SpriteInfo loaderSprite;
	Sprite loader;
	Texture loaderTexture;
	vector<CircleShape> loaderParticles;

	Effect launch;

	RenderWindow window;
};
