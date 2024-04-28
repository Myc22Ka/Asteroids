#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "FileMenager.h"
#include "Game.h"
#include "Score.h"
#include "SpriteData.h"
#include <unordered_map>
#include "PlayerHealthUI.h"

class WindowBox
{
public:
	WindowBox();

	void displayWindow();
	static void init();
	void begin();

	static vector<PlayerHealthUI> playerHealthUIs;
private:
	void spawnEnemy();

	void spawnWind();
	static double windSpawnTime;

	RenderWindow window;
	static double asteroidSpawnTime;
};
