#include "GameFrame.h"
#include "DeathScreen.h"
#include "Game.h"
#include "DashBar.h"
#include "GamePause.h"
#include "WindowBox.h"
#include "Pickup.h"

TextField GameFrame::fps{ 0 };
Wind* GameFrame::wind = nullptr;
GamePause* GameFrame::gamePause = nullptr;

GameFrame::GameFrame() : Page("background")
{
	init();
}

void GameFrame::run(const float& deltaTime, RenderWindow& window)
{
    Page::run(deltaTime, window);

    updateWindow(deltaTime, window);
    Game::spawnEnemy(deltaTime);

    renderUI(window);

    wind->init(deltaTime, window);
    gamePause->init(deltaTime, window);
}

void GameFrame::navigator(Event& e) {
    if (WindowBox::isKeyPressed) return;

    if (Game::getGameState() == PAUSED) {
        gamePause->navigator(e);
        return;
    }

    switch (e.key.code)
    {
    case Keyboard::H:
        Game::hitboxesVisibility = !Game::hitboxesVisibility;
        break;
    case Keyboard::Num7:
        Game::addEntity(new Pickup(physics::getRandomPosition(32)));
        break;
    case Keyboard::Num8:
        Player::playerStats.bulletAmount += 1;
        if (Player::playerStats.bulletAmount == 5) Player::playerStats.bulletAmount = 1;
        break;
    case Keyboard::Num9:
        wind->forceWind(10.0f, 4.0f, physics::getRandomDirection());
        break;
    case Keyboard::Num0:
        Game::freeze.startEffect(physics::getRandomFloatValue(5.0f, 0.5f) + Player::playerStats.time);
        Game::setGameState(FREZZE);
        break;
    case Keyboard::P:
        gamePause->setPrevGameState();
        SoundData::modifySound(Sounds::AMBIENT);
        SoundData::modifySound(Sounds::WIND);
        Game::setGameState(PAUSED);
        break;
    }

    WindowBox::isKeyPressed = true;
}

void GameFrame::init()
{
    Page::init();

    SoundData::sounds[Sounds::AMBIENT].setVolume(100);
    SoundData::playLooped(Sounds::AMBIENT);

    Game::addEntity(new Player());
    Game::enemySpawn.setEffectDuration(FileMenager::timingsData.default_enemy_spawn_time);

    fps.setColorText(Color(255, 255, 255, 150));
    fps.setSize(FileMenager::screenData.fps_font_size);

    Score::init();

    wind = new Wind();
    gamePause = new GamePause();
}

void GameFrame::renderUI(RenderWindow& window)
{
    Score::scoreText.setText(Score::getScoreString());
    window.draw(Score::scoreText.getText());

    if (Score::getScore() / FileMenager::screenData.game_next_level_spike > Game::level && Game::level != Game::maxLevel) Game::level += 1;

    DashBar dashBar;

    dashBar.update(min(1 - Player::dash.getEffectDuration() / FileMenager::playerData.dash_time_delay, 1.0f));
    dashBar.draw(window);
}

void GameFrame::updateWindow(const float& deltaTime, RenderWindow& window)
{
    for (auto& particle : Game::getParticles())
    {
        if (!particle->isActive()) continue;

        particle->render(window);
        particle->update(deltaTime);
    }

    if (!Game::freeze.isEffectActive() && Game::getGameState() == FREZZE) Game::setGameState(PLAYING);
    if (!SoundData::isSoundPlaying(Sounds::AMBIENT) && Game::getGameState() == PLAYING) SoundData::renev(Sounds::AMBIENT);
    if (SoundData::isSoundPlaying(Sounds::WIND) && !wind->isActive()) SoundData::stop(Sounds::WIND);

    for (auto& entity : Game::getEntities())
    {
        if (!entity || !entity->isActive() || (DeathScreen::isScreenOver() && entity->getEntityType() == TYPE_PLAYER)) continue;

        entity->render(window);

        if (Game::getGameState() == DEATH && entity->getEntityType() != TYPE_EXPLOSION && entity->getEntityType() != TYPE_ENEMY_BULLET && entity->getEntityType() != TYPE_BULLET_SINGLE || Game::getGameState() == PAUSED) continue;

        entity->update(deltaTime);
    }

    for (auto& life : Player::playerStats.lifes) {
        life.update(deltaTime);
        life.draw(window);
    }

    fpsDelay.updateEffectDuration(deltaTime);

    if (!fpsDelay.isEffectActive()) {
        fpsDelay.startEffect(0.2f);
        float lastTime = 0;
        fps.setText(to_string(static_cast<int>(1.0f / (deltaTime - lastTime))) + " FPS");
        fps.setTextPosition(Vector2f(FileMenager::screenData.fps_pos_x + FileMenager::screenData.padding, FileMenager::screenData.fps_pos_y + FileMenager::screenData.padding));
        lastTime = deltaTime;
    }

    window.draw(fps.getText());
}