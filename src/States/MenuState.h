#pragma once

#include "Core/GameState.h"
#include <SFML/Graphics.hpp>

class MenuState : public GameState
{
public:
    MenuState();

    void handleEvent(Game& game, const sf::Event& event) override;
    void update(Game& game, float deltaTime) override;
    void render(Game& game) override;

private:
    sf::Font m_font;
    sf::Texture m_backgroundTexture;
    sf::RectangleShape m_backgroundSprite;
    sf::Text m_title;
    sf::Text m_prompt;
};
