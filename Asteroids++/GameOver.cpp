#include "GameOver.h"
#include <regex>
#include "WindowBox.h"

TextField GameOver::gameOver{ 128 };
TextField GameOver::underscore{ 24 };
TextField GameOver::playerNameText{ 24 };
string GameOver::playerName{""};
Sprite GameOver::background{};
Texture GameOver::texture{};

void GameOver::init()
{
    gameOver.setText("Game Over!");
    gameOver.setTextCenterX(100.0f);

    playerNameText.setTextCenterX(500.0f);
    playerNameText.setLetterSpacing(2.05);

    underscore.setText("_");

    if (!texture.loadFromFile("./assets/gameover.png"))
        cout << "Error: Cannot load background!" << endl;

    background.setTexture(texture);
}

void GameOver::enterPlayerName(Event& e)
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

void GameOver::draw(RenderWindow& window)
{
    window.draw(background);

    window.draw(gameOver.getText());

    //window.draw(playerNameText.getText());
}

void GameOver::update(const float& deltaTime)
{
}
