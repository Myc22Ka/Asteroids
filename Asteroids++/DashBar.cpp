#include "DashBar.h"
#include "FileMenager.h"
#include "SoundData.h"
#include "WindowBox.h"

DashBar::DashBar() {
	spriteInfo = getSprite(Sprites::DASHBAR);
	position = Vector2f(float(WindowBox::getVideoMode().width - (spriteInfo.spriteSize >> 1) - FileMenager::screenData.padding), float(spriteInfo.spriteSize >> 2));
}

void DashBar::update(double newCurrentValue)
{
    if (Game::getGameState() == PAUSED) return;

    currentValue = newCurrentValue;
    auto increments = static_cast<int>((currentValue / 0.2) - 0.2);

    spriteInfo.spriteState = min(increments, static_cast<int>(spriteInfo.frames.size()) - 1);
    updateSprite(spriteInfo.sprite, spriteInfo.frames, (int)spriteInfo.spriteState);
}

void DashBar::draw(RenderWindow& window) const
{
	window.draw(spriteInfo.sprite, Transform().translate(position));
}
