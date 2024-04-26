#include "DashBar.h"
#include "FileMenager.h"
#include "SoundData.h"
#include "Player.h"

DashBar::DashBar() {
	spriteInfo = getSprite(Sprites::DASHBAR);
    position = Vector2f(FileMenager::screenData.size_width - (spriteInfo.spriteSize >> 1) - 10, spriteInfo.spriteSize >> 2);
}

void DashBar::update(double newCurrentValue)
{
    currentValue = newCurrentValue;
    int increments = static_cast<int>(currentValue / 0.2) - 0.2;

    spriteInfo.spriteState = min(increments, static_cast<int>(spriteInfo.frames.size()) - 1);
    updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
}

void DashBar::draw(RenderWindow& window) const
{
	window.draw(spriteInfo.sprite, Transform().translate(position));
}
