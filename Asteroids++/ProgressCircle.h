#pragma once

#include <SFML/Graphics.hpp>

class ProgressCircle : public sf::Drawable {
public:
    ProgressCircle(float radius);
    void setValue(float value);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float m_radius;
    sf::Vector2f m_position;
    float m_value = 0.f;
    sf::Font m_font;
    sf::Text m_text;
};