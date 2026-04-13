#include "Core/Config.h"
#include "States/GameOverState.h"
#include "Core/Game.h"
#include "States/MenuState.h"
#include <sstream>

GameOverState::GameOverState(int score, float survivalTime)
    : m_title(m_font),
      m_stats(m_font)
{
    const bool fontLoaded = m_font.openFromFile(Config::FontPath.data());
    (void)fontLoaded;
    const bool backgroundLoaded = m_backgroundTexture.loadFromFile(Config::NightBackgroundPath.data());
    (void)backgroundLoaded;
    m_backgroundSprite.setSize(sf::Vector2f(static_cast<float>(Config::WindowWidth), static_cast<float>(Config::WindowHeight)));
    m_backgroundSprite.setTexture(&m_backgroundTexture, true);

    m_title.setString("Game Over");
    m_title.setCharacterSize(42);
    m_title.setFillColor(sf::Color(255, 236, 180));
    m_title.setOutlineColor(sf::Color(0, 0, 0, 220));
    m_title.setOutlineThickness(3.f);
    m_title.setPosition(sf::Vector2f(500.f, 180.f));

    std::ostringstream builder;
    builder << "Score: " << score << "\n";
    builder << "Survived: " << static_cast<int>(survivalTime) << " seconds\n";
    builder << "Press Enter for Menu";

    m_stats.setString(builder.str());
    m_stats.setCharacterSize(28);
    m_stats.setFillColor(sf::Color(238, 247, 255));
    m_stats.setOutlineColor(sf::Color(0, 0, 0, 200));
    m_stats.setOutlineThickness(2.f);
    m_stats.setPosition(sf::Vector2f(430.f, 300.f));
}

void GameOverState::handleEvent(Game& game, const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Enter)
        {
            game.changeState(std::make_unique<MenuState>());
        }
    }
}

void GameOverState::update(Game&, float)
{
}

void GameOverState::render(Game& game)
{
    game.window().draw(m_backgroundSprite);
    game.window().draw(m_title);
    game.window().draw(m_stats);
}
