#include "Player.h"
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"

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
    shootTimer()
{
	drawHitboxes();
    setPlayerStats();
}

void Player::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
	if(Game::hitboxesVisibility) window.draw(shape, transform);
}

void Player::update(double deltaTime) {
    shootTimer -= deltaTime;
    dashTimer -= deltaTime;

    spriteInfo.currentSpriteLifeTime -= deltaTime;

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

    if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer <= 0) {
        shootTimer = Player::playerStats.shootOffset;
        float radians = angle * (M_PI / 180.0f);

        Game::addToEntities(new Bullet(position, Vector2f(cos(radians), sin(radians)), angle));
        SoundData::play(Sounds::LASER_SHOOT);
    }

    if (!Keyboard::isKeyPressed(Keyboard::Space) && spriteInfo.currentSpriteLifeTime <= 0) {
        spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
        spriteInfo.spriteState = (spriteInfo.spriteState + 1) % spriteInfo.frames.size();
        updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
    }

    collisionDetection();
}

const EntityType Player::getEntityType()
{
	return EntityType::TYPE_PLAYER;
}

void Player::collisionDetection()
{

	position.x = min(max((double)position.x, radius), FileMenager::screenData.size_width - radius);
	position.y = min(max((double)position.y, radius), FileMenager::screenData.size_height - radius);

	for (size_t i = 0; i < Game::entities.size(); i++)
	{
		if (typeid(*Game::entities[i]) == typeid(SingleAsteroid) || typeid(*Game::entities[i]) == typeid(MultiAsteroid)) {
			Asteroid* enemy = dynamic_cast<Asteroid*>(Game::entities[i]);

			if (physics::intersects(position, radius, enemy->position, enemy->radius)) {
				SoundData::play(Sounds::EXPLOSION);
				Game::gameOver();
			}
		}
	}
}

void Player::dashAbility(const double& deltaTime)
{
    const auto animationDuration = FileMenager::playerData.dash_duration;

    if (Keyboard::isKeyPressed(Keyboard::R) && !isDashing && dashTimer <= 0) {
        isDashing = true;
        dashTimer = FileMenager::playerData.dash_time_delay;

        double radians = angle * (M_PI / 180.0f);

        Vector2f endPoint(position.x + cos(radians) * size * FileMenager::playerData.dash_length, position.y + sin(radians) * size * FileMenager::playerData.dash_length);

        SoundData::play(Sounds::DASH_ABILITY);
        thread animationThread([this, endPoint, animationDuration]() {
            this_thread::sleep_for(chrono::milliseconds(50));
            Clock clock;

            while (true) {
                float elapsedTime = clock.getElapsedTime().asSeconds();
                float t = elapsedTime / animationDuration;
                if (t > 1.0f) t = 1.0f;

                Vector2f interpolatedPosition = position + (endPoint - position) * t;
                position = interpolatedPosition;

                if (t >= animationDuration) {
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
    Player::playerStats.shootOffset = FileMenager::playerData.bullet_shoot_delay;
    Player::playerStats.accurancy = 0; // doesnt respected yet.
    Player::playerStats.bulletDamage = 50;
    Player::playerStats.bulletSize = FileMenager::playerData.bullet_size;
    Player::playerStats.bulletSpeed = FileMenager::playerData.bullet_speed;
    Player::playerStats.lifes = 3; // doesnt respected yet.
    Player::playerStats.speed = FileMenager::playerData.speed;
    Player::playerStats.turnSpeed = FileMenager::playerData.turn_speed;
}
