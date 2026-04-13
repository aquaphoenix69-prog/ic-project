#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class HUD
{
public:
    HUD();

    void update(int playerHealth, int score, int enemyCount, const std::string& phaseLabel, float survivalTime);
    void render(sf::RenderWindow& window) const;

private:
    sf::Font m_font;
    sf::Texture m_panelTexture;
    sf::RectangleShape m_panelSprite;
    sf::Text m_healthText;
    sf::Text m_scoreText;
    sf::Text m_enemyText;
    sf::Text m_phaseText;
    sf::Text m_timeText;
};
