#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include "Score.h"
#include "Physics.h"
#include "DashBar.h"
#include "WindowBox.h"
#include "PlayerHealthUI.h"
#include "SingleAsteroid.h"
#include "Wind.h"
#include "DeathScreen.h"
#include "GameFrame.h"

VideoMode WindowBox::videoMode{};
DeathScreen* WindowBox::deathScreen = nullptr;
RenderWindow WindowBox::window{};
bool WindowBox::isKeyPressed{ false };

WindowBox::WindowBox() : counter(0) {}

VideoMode WindowBox::getVideoMode() {
	return videoMode;
}

void WindowBox::displayWindow() {
	//videoMode = VideoMode(1500, 1080);
    videoMode = VideoMode::getDesktopMode();

    window.create(videoMode, "Asteroids++", Style::None);
    window.setFramerateLimit(FileMenager::screenData.framerate);

    deathScreen = new DeathScreen();
    Game::setGameState(MENU_LOADING);

    Clock clock;

    while (window.isOpen()) {
        Event e{};

        while (window.pollEvent(e)) {
            if(e.type == Event::Closed || (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)) close();

            Game::navigate(e);

            if (e.type == Event::KeyReleased) {
                isKeyPressed = false;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();

        Game::runCurrentPage(deltaTime, window);

        deathScreen->init(deltaTime, window);

        window.display();
    }
}

void WindowBox::begin()
{
    Game::setGameState(PLAYING);
    Game::setCurrentPage(new GameFrame());
}

void WindowBox::close()
{
    SoundData::play(Sounds::GOODBYE);
    this_thread::sleep_for(chrono::milliseconds(1000));

    window.close();
}
