#include "PlayerHealthUI.h"
#include "WindowBox.h"

PlayerHealthUI::PlayerHealthUI(const float& offset) : offset(offset), removeHealthFromPlayer(false)
{
    spriteInfo = getSprite(Sprites::HEART);
	position = Vector2f(WindowBox::getVideoMode().width - (spriteInfo.spriteSize >> 1) - FileMenager::screenData.padding - offset, float(getSprite(Sprites::DASHBAR).spriteSize - (spriteInfo.spriteSize << 1)));

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, spriteInfo.hitboxSize);
}

void PlayerHealthUI::update(float deltaTime)
{
	if (Game::freeze.isEffectActive()) return;

	spriteInfo.currentSpriteLifeTime -= deltaTime;

	if (spriteInfo.currentSpriteLifeTime < 0) {
		spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
		spriteInfo.spriteState = (spriteInfo.spriteState + 1) % (!removeHealthFromPlayer ? 15 : spriteInfo.frames.size());
		updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
	}
}

void PlayerHealthUI::draw(RenderWindow& window) const
{
	if (removeHealthFromPlayer && spriteInfo.spriteState == spriteInfo.frames.size() - 1) {
		Player::playerStats.lifes.pop_back();
		return;
	}

	window.draw(spriteInfo.sprite, Transform().translate(position));
}

void PlayerHealthUI::setSpriteState(const int& newState)
{
	spriteInfo.spriteState = newState;
}

void PlayerHealthUI::removeHealth()
{
	removeHealthFromPlayer = true;
}