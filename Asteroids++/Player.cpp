#include "Player.h"
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"
#include "SingleBullet.h"
#include "WindowBox.h"
#include "Particle.h"
#include "DeathScreen.h"

float Player::dashTimer = 0.0f;
PlayerStats Player::playerStats{ 
    FileMenager::playerData.bullet_shoot_delay,
    FileMenager::playerData.turn_speed,
    3.0f,
    0.0f,
    FileMenager::playerData.bullet_shoot_delay,
    1.0f,
    FileMenager::playerData.bullet_size,
    50.0f,
    FileMenager::playerData.bullet_speed,
    {false, false},
    { 10.0f, false },
    { 10.0f, false },
    { 10.0f, false },
    { 10.0f, false }
};

Player::Player() :
	Entity(
        Vector2f(FileMenager::playerData.start_position_x, FileMenager::playerData.start_position_y), 
        FileMenager::playerData.start_position_angle, 
        FileMenager::playerData.size, 
        Color::Blue,
        getSprite(Sprites::SHIP)
    ), 
    shootTimer(),
    invincibilityFrames(0.0f),
    dead(false)
{
    shieldSprite = getSprite(Sprites::SHIELD);
	drawHitboxes();
    setPlayerStats();
}

void Player::render(RenderWindow& window)
{
    if (delay.isEffectActive() || dead) return;

	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
    if (playerStats.shield.isEffectActive()) {
        window.draw(shieldSprite.sprite, transform.rotate(-angle));
        playerStats.shield.getBar()->draw(window);
    }
	if(Game::hitboxesVisibility) window.draw(shape, transform);
    if (playerStats.drunkMode.isEffectActive()) playerStats.drunkMode.getBar()->draw(window);
    if (playerStats.scoreTimes2.isEffectActive()) playerStats.scoreTimes2.getBar()->draw(window);
    if (playerStats.scoreTimes5.isEffectActive()) playerStats.scoreTimes5.getBar()->draw(window);
}

void Player::update(float deltaTime) {
    if (dead) {
        Game::addEntity(new Explosion(position, size, getSprite(Sprites::EXPLOSION_1), true));
        dead = false;
        delay.startEffect(0.7f);
        return;
    }

    delay.updateEffectDuration(deltaTime);

    if (delay.isEffectActive()) return;

    shootTimer -= deltaTime;
    dashTimer -= deltaTime;
    invincibilityFrames -= deltaTime;

    spriteInfo.currentSpriteLifeTime -= deltaTime;

    updatePosition(deltaTime);
    dashAbility(deltaTime);

    if (isDashing) Game::addParticle(new Particle(position, angle, Sprites::SHIP, Color(126, 193, 255, 100), 0.15));

    if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer <= 0.0f) {
        shootTimer = Player::playerStats.shootOffset;
        float radians = angle * (physics::getPI() / 180.0f);

        Game::addEntity(new SingleBullet(position, Vector2f(cos(radians), sin(radians)), angle));
        SoundData::play(Sounds::LASER_SHOOT);
    }

    if (!Keyboard::isKeyPressed(Keyboard::Space) && spriteInfo.currentSpriteLifeTime <= 0) {
        spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
        spriteInfo.spriteState = (spriteInfo.spriteState + 1) % spriteInfo.frames.size();
        updateSprite(spriteInfo.sprite, spriteInfo.frames, (int)spriteInfo.spriteState);
    }

    if (playerStats.shield.isEffectActive()) {
        shieldSprite.currentSpriteLifeTime -= deltaTime;
        playerStats.shield.updateEffectDuration(deltaTime);

        setSpriteFullCycle(shieldSprite);
    }

    if(invincibilityFrames < 0 && !playerStats.shield.isEffectActive()) collisionDetection();
}

void Player::updatePosition(const float& deltaTime) {
    if (!isDashing) {
        float turnDirection = 0.0f;

        if (playerStats.drunkMode.isEffectActive()) {
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                turnDirection -= 1.0f;
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                turnDirection += 1.0f;
            }
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                turnDirection -= 1.0f;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                turnDirection += 1.0f;
            }
        }

        angle += playerStats.turnSpeed * turnDirection * deltaTime;
    }

    if (Keyboard::isKeyPressed(Keyboard::W)) {
        float radians = angle * (physics::getPI() / 180.0f);

        position.x += cos(radians) * playerStats.speed * deltaTime;
        position.y += sin(radians) * playerStats.speed * deltaTime;
    }

    position.x = min(max(position.x, radius), WindowBox::getVideoMode().width - radius);
	position.y = min(max(position.y, radius), WindowBox::getVideoMode().height - radius);

    updateStatsbars(deltaTime);
}

const EntityType Player::getEntityType()
{
	return EntityType::TYPE_PLAYER;
}

void Player::collisionDetection()
{
    Game::foreachEntity([this](Entity* entity) {
        if (auto* asteroid = dynamic_cast<Asteroid*>(entity))
        {
            if (!physics::intersects(position, radius, asteroid->position, asteroid->radius))
                return;

            invincibilityFrames = 5.0f;
            playerStats.lifes -= 1;
			WindowBox::playerHealthUIs.back().death = true;
			WindowBox::playerHealthUIs.back().setSpriteState(16);
            SoundData::play(Sounds::EXPLOSION);

            Game::addEntity(new Explosion(position, size));

            if (playerStats.lifes == 0) {
                Game::gameOver();
			    return;
            }

            Game::setGameState(PAUSED);
			DeathScreen::setDelay(0.7f);
			DeathScreen::activateDeathScreen(1.75f);

            dead = true;
        }
    });
}

void Player::dashAbility(const float& deltaTime)
{
    const auto animationDuration = FileMenager::playerData.dash_duration;

    if (Keyboard::isKeyPressed(Keyboard::R) && !isDashing && dashTimer <= 0) {
        isDashing = true;
        dashTimer = FileMenager::playerData.dash_time_delay;
        invincibilityFrames = 0;

        float radians = angle * (physics::getPI() / 180.0f);

        Vector2f endPoint(position.x + cos(radians) * size * FileMenager::playerData.dash_length, position.y + sin(radians) * size * FileMenager::playerData.dash_length);

        if(invincibilityFrames <= 0) SoundData::play(Sounds::DASH_ABILITY);
        thread animationThread([this, endPoint, animationDuration]() {
            this_thread::sleep_for(chrono::milliseconds(50));
            Clock clock;

            while (true) {
                float elapsedTime = clock.getElapsedTime().asSeconds();
                float t = elapsedTime / animationDuration;
                if (t > 1.0f) t = 1.0f;

                Vector2f interpolatedPosition = position + (endPoint - position) * t;
                position = interpolatedPosition;

                if (t >= animationDuration || this->invincibilityFrames > 0) {
                    isDashing = false;
                    break;
                }

                this_thread::sleep_for(chrono::milliseconds(10));
            }
        });

        animationThread.detach();
    }
}

void Player::setPlayerStats()
{
    playerStats.shootOffset = FileMenager::playerData.bullet_shoot_delay;
    playerStats.accurancy = 1; // doesnt respected yet.
    playerStats.bulletDamage = 50;
    playerStats.bulletSize = FileMenager::playerData.bullet_size;
    playerStats.bulletSpeed = FileMenager::playerData.bullet_speed;
    playerStats.lifes = 3;
    playerStats.speed = FileMenager::playerData.speed;
    playerStats.turnSpeed = FileMenager::playerData.turn_speed;
    playerStats.shield = { 10.0f, false, new Bar(radius, 2.0f, Color::Blue, Color::Black, playerStats.drunkMode.getEffectDuration(), Vector2f(-100.0f, -100.0f), Sprites::PICKUP_SHIELD)};
    playerStats.drunkMode = { 10.0f, false, new Bar(radius, 2.0f, Color::Color(242, 142, 28, 255), Color::Black, playerStats.drunkMode.getEffectDuration(), Vector2f(-100.0f, -100.0f), Sprites::PICKUP_DRUNKMODE) };
    playerStats.scoreTimes2 = { 10.0f, false, new Bar(radius, 2.0f, Color::Color(144, 238, 144, 255), Color::Black, playerStats.drunkMode.getEffectDuration(), Vector2f(-100.0f, -100.0f), Sprites::PICKUP_TIMES_2) };
    playerStats.scoreTimes5 = { 10.0f, false, new Bar(radius, 2.0f, Color::Color(93, 213, 93, 255), Color::Black, playerStats.drunkMode.getEffectDuration(), Vector2f(-100.0f, -100.0f), Sprites::PICKUP_TIMES_5) };

    playerStats.bulletType.piercing = false;
    playerStats.bulletType.homing = true;
}

Sprites Player::getPlayerBulletSprite()
{
    if (playerStats.bulletType.homing) return  Sprites::HOMING_BULLET;

    if (playerStats.bulletType.piercing) return Sprites::PIERCING_BULLET;

    return Sprites::SINGLE_BULLET;
}

void Player::updateStatsbars(const float& deltaTime) {
    float offset = 0.0f;

    if (playerStats.drunkMode.isEffectActive()) {
        playerStats.drunkMode.updateEffectDuration(deltaTime);

        playerStats.drunkMode.getBar()->updateValue(playerStats.drunkMode.getEffectDuration());
        playerStats.drunkMode.getBar()->updatePosition(Vector2f{ position.x - ((int)radius >> 1), position.y + radius + offset });

        offset += 10.0f;
    }

    if (playerStats.shield.isEffectActive()) {
        playerStats.shield.updateEffectDuration(deltaTime);

        playerStats.shield.getBar()->updateValue(playerStats.shield.getEffectDuration());
        playerStats.shield.getBar()->updatePosition(Vector2f{ position.x - ((int)radius >> 1), position.y + radius + offset });

        offset += 10.0f;
    }

    if (playerStats.scoreTimes2.isEffectActive()) {
        playerStats.scoreTimes2.updateEffectDuration(deltaTime);

        playerStats.scoreTimes2.getBar()->updateValue(playerStats.scoreTimes2.getEffectDuration());
        playerStats.scoreTimes2.getBar()->updatePosition(Vector2f{ position.x - ((int)radius >> 1), position.y + radius + offset });

        offset += 10.0f;
    }

    if (playerStats.scoreTimes5.isEffectActive()) {
        playerStats.scoreTimes5.updateEffectDuration(deltaTime);

        playerStats.scoreTimes5.getBar()->updateValue(playerStats.scoreTimes5.getEffectDuration());
        playerStats.scoreTimes5.getBar()->updatePosition(Vector2f{ position.x - ((int)radius >> 1), position.y + radius + offset });

        offset += 10.0f;
    }
}