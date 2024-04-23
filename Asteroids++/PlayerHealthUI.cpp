#include "PlayerHealthUI.h"
#include "WindowBox.h"

PlayerHealthUI::PlayerHealthUI(Vector2f position) : position(position)
{
    spriteInfo = getSprite(Sprites::HEART);

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, spriteInfo.hitboxSize);
}

void PlayerHealthUI::update()
{
	spriteInfo.spriteState = (spriteInfo.spriteState + 1) % spriteInfo.frames.size();
	updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
}

void PlayerHealthUI::draw(RenderWindow& window) const
{
	window.draw(spriteInfo.sprite, Transform().translate(position));
}
