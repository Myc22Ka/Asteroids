#include "ProgressCircle.h"
#include "FileMenager.h"
#include <iostream>

ProgressCircle::ProgressCircle(float radius) : m_radius(radius) {
    m_font.loadFromFile("./assets/font.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(FileMenager::screenData.size_width - 60, FileMenager::screenData.size_height - 34);
}

void ProgressCircle::setValue(float value) {
    m_value = std::min(std::max(value * 100, 0.f), 100.f);
    m_text.setString(std::to_string(static_cast<int>(m_value)) + "%");
}

void ProgressCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_text, states);
}