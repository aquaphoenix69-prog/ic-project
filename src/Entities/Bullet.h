#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(const sf::Texture& texture, const sf::Vector2f& startPosition, const sf::Vector2f& velocity);

    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;
    void destroy();

    sf::Vector2f position() const;
    sf::FloatRect bounds() const;
    bool isAlive() const;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    bool m_alive;
};
