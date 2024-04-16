#include "SpriteData.h"

const auto defaultDir = "./assets/sprites";

unordered_map<string, SpriteInfo> SpriteData::sprites;

void SpriteData::loadAllSprites()
{

    for (const auto& entry : fs::directory_iterator(defaultDir)) {
        if (fs::is_regular_file(entry.path()) && entry.path().extension() == ".png") {
            const auto filename = entry.path().stem().string();
            
            initSprite(filename);

            if (!sprites[filename].texture.loadFromFile(entry.path().string())) {
                cout << "Error: Invalid Sprite Name\n" << endl;
                return;
            }

            sprites[filename].texture.setSmooth(true);

            const auto w = getTextureWidth(sprites[filename].texture) / sprites[filename].size;
            const auto h = getTextureHeight(sprites[filename].texture) / sprites[filename].size;
            const auto n = w * h;

            int y = 0;
            for (int i = 0; i < h; i++)
            {
                int x = 0;
                for (int i = 0; i < w; i++)
                {
                    const auto rect = sf::IntRect(x, y, sprites[filename].size, sprites[filename].size);
                    sprites[filename].frames.push_back(rect);
                    x += sprites[filename].size;
                }
                y += sprites[filename].size;
            }
            sprites[filename].sprite.setTexture(sprites[filename].texture);
            sprites[filename].sprite.setTextureRect(sprites[filename].frames[0]);
            sprites[filename].sprite.rotate(sprites[filename].rotation);

            const sf::Rect center = sprites[filename].sprite.getLocalBounds();
            sprites[filename].sprite.setOrigin((int)center.width >> 1, (int)center.height >> 1);
        }
    }

}

SpriteInfo SpriteData::getSprite(const Sprites& spriteType)
{
    for (const auto& pair : sprites) {
        if (pair.second.spriteType == spriteType) {
            return pair.second;
        }
    }
    return SpriteInfo();
}

void SpriteData::setRotation(Sprite& sprite, const int& angle)
{
    sprite.rotate(angle);
}

void SpriteData::updateSprite(Sprite& sprite, const vector<IntRect>& frames, const int& spriteState)
{
    sprite.setTextureRect(frames[spriteState]);
}

void SpriteData::loadFullCycleSprite(SpriteInfo& spriteInfo, float deltaTime)
{
    spriteInfo.isAnimating = true;
    spriteInfo.spriteLifeTime -= deltaTime;

    thread animationThread([&]() {
        for (int i = 0; i < spriteInfo.frames.size(); ++i) {
            spriteInfo.spriteState = i;
            updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    animationThread.detach();
    spriteInfo.isAnimating = false;
}

void SpriteData::initSprite(const string& filename){
    if (filename == "ship") {
        sprites[filename].spriteType = Sprites::SHIP;
        sprites[filename].spriteState = 0;
        sprites[filename].rotation = 90;
        sprites[filename].size = 64;
        return;
    }
    if (filename == "asteroid") {
        sprites[filename].spriteType = Sprites::ASTEROID;
        sprites[filename].spriteState = 0;
        sprites[filename].rotation = 0;
        sprites[filename].size = 64;
        return;
    }
    if (filename == "bullet") {
        sprites[filename].spriteType = Sprites::BULLET;
        sprites[filename].spriteState = 0;
        sprites[filename].rotation = 45;
        sprites[filename].size = 64;
        return;
    }
    if (filename == "explosion") {
        sprites[filename].spriteType = Sprites::EXPLOSION;
        sprites[filename].spriteState = 0;
        sprites[filename].rotation = 0;
        sprites[filename].size = 128;
        sprites[filename].spriteLifeTime = 0.15;
        return;
    }
}

const int SpriteData::getTextureWidth(const Texture& texture)
{
    return texture.getSize().x;
}

const int SpriteData::getTextureHeight(const Texture& texture)
{
    return texture.getSize().y;
}