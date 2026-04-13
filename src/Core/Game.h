#pragma once

#include "Core/GameState.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
public:
    Game();

    void run();
    void changeState(std::unique_ptr<GameState> nextState);
    void close();

    sf::RenderWindow& window();
    const sf::RenderWindow& window() const;

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow m_window;
    std::unique_ptr<GameState> m_state;
};
