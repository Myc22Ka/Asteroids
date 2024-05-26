#include "MenuLoader.h"
#include "WindowBox.h"

MenuLoader::MenuLoader() : Page("loader")
{
	init();
}

void MenuLoader::init()
{
	Page::init();

	loaderSprite = SpriteData::getSprite(Sprites::LOADER);

	launch.startEffect(FileMenager::screenData.launch_time);

	loadParticles();
}

void MenuLoader::run(const float& deltaTime, RenderWindow& window)
{
	Page::run(deltaTime, window);

	auto color = getBackgroundColor();

	if (launch.isEffectActive() && loaderSprite.spriteState != loaderSprite.frames.size() - 1) {
		launch.updateEffectDuration(deltaTime);
		float opacity = 255.0f * (1 - launch.getEffectDuration() / FileMenager::screenData.launch_time);

		color.a = static_cast<Uint8>(opacity);

		setBackgroundColor(color);
		loaderSprite.sprite.setColor(color);
	}

	if (!launch.isEffectActive()) {
		loaderSprite.currentSpriteLifeTime -= deltaTime;

		if (loaderSprite.spriteState == loaderSprite.frames.size() - 1)
			launch.startEffect(FileMenager::screenData.launch_time);

		if (loaderSprite.currentSpriteLifeTime <= 0) {
			loaderSprite.currentSpriteLifeTime = loaderSprite.defaultSpriteLifeTime;
			loaderSprite.spriteState = (loaderSprite.spriteState + 1) % loaderSprite.frames.size();
			SpriteData::updateSprite(loaderSprite.sprite, loaderSprite.frames, loaderSprite.spriteState);
		}
	};

	if (launch.isEffectActive() && loaderSprite.spriteState == loaderSprite.frames.size() - 1) {
		launch.updateEffectDuration(deltaTime);
		float opacity = 255.0f * (launch.getEffectDuration() / FileMenager::screenData.launch_time);

		color.a = static_cast<Uint8>(opacity);

		setBackgroundColor(color);
		loaderSprite.sprite.setColor(color);

		if (!launch.isEffectActive() && loaderSprite.spriteState == loaderSprite.frames.size() - 1) Game::setGameState(MENU);
	}

	window.draw(loaderSprite.sprite, Transform().translate(Vector2f(WindowBox::getVideoMode().width >> 1, WindowBox::getVideoMode().height >> 1)));

	for (auto& [circle, velocity] : loaderParticles) {
		velocity.x += sin(circle.getPosition().y / 0.5f);

		circle.move(velocity);

		Color c = circle.getFillColor();
		c.a = min(color.a, static_cast<Uint8>(FileMenager::screenData.launch_particle_opacity));

		circle.setFillColor(c);

		FloatRect bounds(-circle.getRadius(), -circle.getRadius(), window.getSize().x + circle.getRadius(), window.getSize().y + circle.getRadius());

		if (!bounds.contains(circle.getPosition())) {
			if (circle.getPosition().x < bounds.left)
				circle.setPosition(bounds.left + bounds.width, circle.getPosition().y);
			else if (circle.getPosition().x > bounds.left + bounds.width)
				circle.setPosition(bounds.left, circle.getPosition().y);
			if (circle.getPosition().y < bounds.top)
				circle.setPosition(circle.getPosition().x, bounds.top + bounds.height);
			else if (circle.getPosition().y > bounds.top + bounds.height)
				circle.setPosition(circle.getPosition().x, bounds.top);
		}

		window.draw(circle);
	}
}

void MenuLoader::navigator(Event& e) {}

void MenuLoader::loadParticles() {
	for (size_t i = 0; i < 50; i++) {
		CircleShape circle(physics::getRandomFloatValue(10.0f, 1.5f));
		circle.setPosition(physics::getRandomPosition(circle.getRadius()));
		circle.setFillColor(Color(208, 241, 255, FileMenager::screenData.launch_particle_opacity));
		const auto velocity = Vector2f(physics::getRandomFloatValue(2.5f), physics::getRandomFloatValue(physics::getPI() / 2, 0.2f));
		loaderParticles.push_back({ circle, velocity });
	}
}