#include "GameOver.h"
#include <regex>
#include "WindowBox.h"

GameOver::GameOver() : Page("gameover"),
    gameOver(128), 
    underscore(24), 
    playerNameText(24), 
    playerName("")
{
    init();
}

void GameOver::init()
{
    Page::init();
    SoundData::recoverSound(Sounds::AMBIENT);
    SoundData::stop(Sounds::AMBIENT);

    gameOver.setText("Game Over!");
    gameOver.setTextCenterX(100.0f);

    playerNameText.setTextCenterX(500.0f);
    playerNameText.setLetterSpacing(2.05);

    underscore.setText("_");
}

void GameOver::drawPlayerName(RenderWindow& window) {
    const auto offset = 10.0f;

    float centerX = (WindowBox::getVideoMode().width - underscore.getText().getGlobalBounds().width * 12 - offset * 11) / 2.0f;
    float centerY = WindowBox::getVideoMode().height / 2.0f;

    for (int i = 0; i < 13; ++i) {
        underscore.setTextPosition(Vector2f(centerX + i * (underscore.getText().getGlobalBounds().width + offset), centerY));
        window.draw(underscore.getText());
    }

    playerNameText.setTextPosition(Vector2f(centerX, centerY - 5.0f));
    window.draw(playerNameText.getText());
}

void GameOver::run(const float& deltaTime, RenderWindow& window)
{
    Page::run(deltaTime, window);

    gameOver.draw(window);

    drawPlayerName(window);
}

void GameOver::navigator(Event& e)
{
    if (e.type == Event::TextEntered) {
        if (e.text.unicode == '\b' && !playerName.empty()) {
            playerName.pop_back();
        }
        else if (e.text.unicode < 128 && e.text.unicode != '\r') {
            string newChar(1, static_cast<char>(e.text.unicode));
            if (playerName.size() < 13 && regex_match(newChar, regex("[A-Za-z0-9]+"))) {
                playerName += newChar;
            }
        }
    }

    playerNameText.setText(playerName);

    if (playerNameText.getText().getString().isEmpty()) return;

    if (Keyboard::isKeyPressed(Keyboard::Enter) && !WindowBox::isKeyPressed) {
        FileMenager::saveData("highscore.txt", pair<string, size_t>(playerName, Score::getScore()));
        FileMenager::highScore = FileMenager::sortMapByFloat(FileMenager::getDataFromFile("highscore.txt"));

        playerName.clear();
        Score::clear();
        Game::setGameState(MENU_HIGHSCORE);
        Game::clearEntities();
        Game::clearParticles();
        Game::level = 1;
        Player::playerStats.lifes.clear();

        WindowBox::isKeyPressed = true;
    }
}