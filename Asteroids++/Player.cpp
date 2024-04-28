#include "Player.h"
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"
#include "SingleBullet.h"
#include "WindowBox.h"
#include "Particle.h"

constexpr double M_PI = 3.14159265358979323846;
double Player::dashTimer = 0.0;
PlayerStats Player::playerStats;

Player::Player() :
	Entity(
        Vector2f(FileMenager::playerData.start_position_x, FileMenager::playerData.start_position_y), 
        FileMenager::playerData.start_position_angle, 
        FileMenager::playerData.size, 
        Color::Blue,
        getSprite(Sprites::SHIP)
    ), 
    shootTimer(),
    invincibilityFrames(0)
{

    shield = getSprite(Sprites::SHIELD);
	drawHitboxes();
    setPlayerStats();
}

void Player::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
    window.draw(shield.sprite, transform.rotate(-angle));
	if(Game::hitboxesVisibility) window.draw(shape, transform);
}

void Player::update(float deltaTime) {
    shootTimer -= deltaTime;
    dashTimer -= deltaTime;
    invincibilityFrames -= deltaTime;
    shield.currentSpriteLifeTime -= deltaTime;

    spriteInfo.currentSpriteLifeTime -= deltaTime;

    if (Keyboard::isKeyPressed(Keyboard::P)) {
        Game::removeEntity(this);
        return;
    };

    if (Keyboard::isKeyPressed(Keyboard::A) && !isDashing) {
        angle -= playerStats.turnSpeed * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && !isDashing) {
        angle += playerStats.turnSpeed * deltaTime;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        float radians = angle * (M_PI / 180.0f);

        position.x += cos(radians) * playerStats.speed * deltaTime;
        position.y += sin(radians) * playerStats.speed * deltaTime;
    }

    dashAbility(deltaTime);

    if (isDashing) Game::addParticle(new Particle(position, angle, Sprites::SHIP, Color(126, 193, 255, 100), 0.15));

    if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer <= 0) {
        shootTimer = Player::playerStats.shootOffset;
        float radians = angle * (M_PI / 180.0f);

        Game::addEntity(new SingleBullet(position, Vector2f(cos(radians), sin(radians)), angle));
        SoundData::play(Sounds::LASER_SHOOT);
    }

    if (!Keyboard::isKeyPressed(Keyboard::Space) && spriteInfo.currentSpriteLifeTime <= 0) {
        spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
        spriteInfo.spriteState = (spriteInfo.spriteState + 1) % spriteInfo.frames.size();
        updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
    }

    position.x = min(max((double)position.x, radius), FileMenager::screenData.size_width - radius);
    position.y = min(max((double)position.y, radius), FileMenager::screenData.size_height - radius);

    setSpriteFullCycle(shield);

    if(invincibilityFrames < 0) collisionDetection();
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

            SoundData::play(Sounds::EXPLOSION);
            resetPlayerStats();
            playerStats.lifes -= 1;
            WindowBox::playerHealthUIs.back().death = true;
            WindowBox::playerHealthUIs.back().setSpriteState(16);
            invincibilityFrames = 5;

            if (playerStats.lifes == 0)
                Game::gameOver();
        }
    });
}

void Player::dashAbility(const double& deltaTime)
{
    const auto animationDuration = FileMenager::playerData.dash_duration;

    if (Keyboard::isKeyPressed(Keyboard::R) && !isDashing && dashTimer <= 0) {
        isDashing = true;
        dashTimer = FileMenager::playerData.dash_time_delay;
        invincibilityFrames = 0;

        double radians = angle * (M_PI / 180.0f);

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

void Player::resetPlayerStats()
{
    auto currentPlayerLifes = playerStats.lifes;
    setPlayerStats();

    playerStats.lifes = currentPlayerLifes;
    position = Vector2f(FileMenager::playerData.start_position_x, FileMenager::playerData.start_position_y);
}

void Player::setPlayerStats()
{
    playerStats.shootOffset = FileMenager::playerData.bullet_shoot_delay;
    playerStats.accurancy = 0; // doesnt respected yet.
    playerStats.bulletDamage = 50;
    playerStats.bulletSize = FileMenager::playerData.bullet_size;
    playerStats.bulletSpeed = FileMenager::playerData.bullet_speed;
    playerStats.lifes = 3;
    playerStats.speed = FileMenager::playerData.speed;
    playerStats.turnSpeed = FileMenager::playerData.turn_speed;

    playerStats.bulletType.piercing = { false };
    playerStats.bulletType.homing = { true };
}

Sprites Player::getPlayerBulletSprite()
{
    if (playerStats.bulletType.piercing) return Sprites::PIERCING_BULLET;

    if (playerStats.bulletType.homing) return  Sprites::HOMING_BULLET;

    return Sprites::SINGLE_BULLET;
}