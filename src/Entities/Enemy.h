#pragma once

#include <SFML/Graphics.hpp>

enum class EnemyType
{
    Cannibal,
    Zombie
};

class Enemy
{
public:
    Enemy(EnemyType type, const sf::Texture& texture, const sf::Vector2f& startPosition);

    void update(float deltaTime, const sf::Vector2f& playerPosition);
    void render(sf::RenderWindow& window) const;
    void takeDamage(int amount);

    sf::Vector2f position() const;
    sf::FloatRect bounds() const;
    bool isAlive() const;
    int damage() const;
    EnemyType type() const;

private:
    sf::RectangleShape m_shape;
    EnemyType m_type;
    float m_speed;
    int m_health;
    int m_damage;
};
