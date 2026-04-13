#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleEvent(Game& game, const sf::Event& event) = 0;
    virtual void update(Game& game, float deltaTime) = 0;
    virtual void render(Game& game) = 0;
};
