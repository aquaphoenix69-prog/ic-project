#include "Core/Game.h"
#include "Core/Config.h"
#include "States/MenuState.h"

Game::Game()
    : m_window(sf::VideoMode({Config::WindowWidth, Config::WindowHeight}), "Survival Island")
{
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    changeState(std::make_unique<MenuState>());
}

void Game::run()
{
    sf::Clock clock;

    while (m_window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::changeState(std::unique_ptr<GameState> nextState)
{
    m_state = std::move(nextState);
}

void Game::close()
{
    m_window.close();
}

sf::RenderWindow& Game::window()
{
    return m_window;
}

const sf::RenderWindow& Game::window() const
{
    return m_window;
}

void Game::processEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            close();
            return;
        }

        if (m_state)
        {
            m_state->handleEvent(*this, *event);
        }
    }
}

void Game::update(float deltaTime)
{
    if (m_state)
    {
        m_state->update(*this, deltaTime);
    }
}

void Game::render()
{
    m_window.clear(sf::Color(20, 40, 50));

    if (m_state)
    {
        m_state->render(*this);
    }

    m_window.display();
}
