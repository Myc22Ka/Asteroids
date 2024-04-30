#include "PlayerHealthUI.h"
#include "WindowBox.h"

PlayerHealthUI::PlayerHealthUI(const double& offset) : offset(offset)
{
    spriteInfo = getSprite(Sprites::HEART);
	position = Vector2f(FileMenager::screenData.size_width - (spriteInfo.spriteSize >> 1) - 10 - offset, getSprite(Sprites::DASHBAR).spriteSize >> 1 - spriteInfo.spriteSize);

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, spriteInfo.hitboxSize);
}

void PlayerHealthUI::update(float deltaTime)
{
	if (Game::freeze.isEffectActive()) return;

	spriteInfo.currentSpriteLifeTime -= deltaTime;

	if (spriteInfo.currentSpriteLifeTime < 0) {
		spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
		spriteInfo.spriteState = (spriteInfo.spriteState + 1) % (!death ? 15 : spriteInfo.frames.size());
		updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
	}
}

void PlayerHealthUI::draw(RenderWindow& window) const
{
	if (death && spriteInfo.spriteState == spriteInfo.frames.size() - 1) {
		WindowBox::playerHealthUIs.pop_back();
		return;
	}

	window.draw(spriteInfo.sprite, Transform().translate(position));
}

void PlayerHealthUI::setSpriteState(const int& newState)
{
	spriteInfo.spriteState = newState;
}
