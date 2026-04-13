#include "Core/Config.h"
#include "UI/HUD.h"
#include <sstream>

HUD::HUD()
    : m_healthText(m_font),
      m_scoreText(m_font),
      m_enemyText(m_font),
      m_phaseText(m_font),
      m_timeText(m_font)
{
    const bool fontLoaded = m_font.openFromFile(Config::FontPath.data());
    (void)fontLoaded;
    const bool panelLoaded = m_panelTexture.loadFromFile(Config::HudPanelPath.data());
    (void)panelLoaded;

    m_panelSprite.setSize(sf::Vector2f(320.f, 120.f));
    m_panelSprite.setTexture(&m_panelTexture, true);
    m_panelSprite.setPosition(sf::Vector2f(12.f, 12.f));

    m_healthText.setCharacterSize(22);
    m_scoreText.setCharacterSize(22);
    m_enemyText.setCharacterSize(22);
    m_phaseText.setCharacterSize(22);
    m_timeText.setCharacterSize(22);

    m_healthText.setOutlineColor(sf::Color(0, 0, 0, 180));
    m_healthText.setOutlineThickness(2.f);
    m_scoreText.setOutlineColor(sf::Color(0, 0, 0, 180));
    m_scoreText.setOutlineThickness(2.f);
    m_enemyText.setOutlineColor(sf::Color(0, 0, 0, 180));
    m_enemyText.setOutlineThickness(2.f);
    m_phaseText.setOutlineColor(sf::Color(0, 0, 0, 180));
    m_phaseText.setOutlineThickness(2.f);
    m_timeText.setOutlineColor(sf::Color(0, 0, 0, 180));
    m_timeText.setOutlineThickness(2.f);

    m_healthText.setFillColor(sf::Color(244, 248, 228));
    m_scoreText.setFillColor(sf::Color(244, 248, 228));
    m_enemyText.setFillColor(sf::Color(244, 248, 228));
    m_phaseText.setFillColor(sf::Color(255, 230, 168));
    m_timeText.setFillColor(sf::Color(244, 248, 228));

    m_healthText.setPosition(sf::Vector2f(28.f, 26.f));
    m_scoreText.setPosition(sf::Vector2f(28.f, 50.f));
    m_enemyText.setPosition(sf::Vector2f(28.f, 74.f));
    m_phaseText.setPosition(sf::Vector2f(28.f, 98.f));
    m_timeText.setPosition(sf::Vector2f(170.f, 98.f));
}

void HUD::update(int playerHealth, int score, int enemyCount, const std::string& phaseLabel, float survivalTime)
{
    std::ostringstream timeBuilder;
    timeBuilder << static_cast<int>(survivalTime);

    m_healthText.setString("Health: " + std::to_string(playerHealth));
    m_scoreText.setString("Score: " + std::to_string(score));
    m_enemyText.setString("Enemies: " + std::to_string(enemyCount));
    m_phaseText.setString("Phase: " + phaseLabel);
    m_timeText.setString("Time: " + timeBuilder.str());
}

void HUD::render(sf::RenderWindow& window) const
{
    window.draw(m_panelSprite);
    window.draw(m_healthText);
    window.draw(m_scoreText);
    window.draw(m_enemyText);
    window.draw(m_phaseText);
    window.draw(m_timeText);
}
