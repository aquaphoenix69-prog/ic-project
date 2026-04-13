#include "Core/Config.h"
#include "States/MenuState.h"
#include "Core/Game.h"
#include "States/GameplayState.h"

MenuState::MenuState()
    : m_title(m_font),
      m_prompt(m_font)
{
    const bool fontLoaded = m_font.openFromFile(Config::FontPath.data());
    (void)fontLoaded;
    const bool backgroundLoaded = m_backgroundTexture.loadFromFile(Config::DayBackgroundPath.data());
    (void)backgroundLoaded;
    m_backgroundSprite.setSize(sf::Vector2f(static_cast<float>(Config::WindowWidth), static_cast<float>(Config::WindowHeight)));
    m_backgroundSprite.setTexture(&m_backgroundTexture, true);

    m_title.setString("SURVIVAL ISLAND");
    m_title.setCharacterSize(52);
    m_title.setFillColor(sf::Color(255, 242, 192));
    m_title.setOutlineColor(sf::Color(24, 20, 16, 210));
    m_title.setOutlineThickness(3.f);
    m_title.setPosition(sf::Vector2f(360.f, 180.f));

    m_prompt.setString("WASD to move   SPACE to fire   ENTER to start");
    m_prompt.setCharacterSize(28);
    m_prompt.setFillColor(sf::Color(240, 250, 242));
    m_prompt.setOutlineColor(sf::Color(0, 0, 0, 190));
    m_prompt.setOutlineThickness(2.f);
    m_prompt.setPosition(sf::Vector2f(240.f, 610.f));
}

void MenuState::handleEvent(Game& game, const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Enter)
        {
            game.changeState(std::make_unique<GameplayState>());
        }
    }
}

void MenuState::update(Game&, float)
{
}

void MenuState::render(Game& game)
{
    game.window().draw(m_backgroundSprite);
    game.window().draw(m_title);
    game.window().draw(m_prompt);
}
