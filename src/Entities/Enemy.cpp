#include "Entities/Enemy.h"
#include <cmath>

namespace
{
sf::Vector2f normalize(const sf::Vector2f& value)
{
    const float length = std::sqrt((value.x * value.x) + (value.y * value.y));
    if (length == 0.f)
    {
        return sf::Vector2f(0.f, 0.f);
    }

    return sf::Vector2f(value.x / length, value.y / length);
}
}

Enemy::Enemy(EnemyType type, const sf::Texture& texture, const sf::Vector2f& startPosition)
    : m_type(type),
      m_speed(type == EnemyType::Cannibal ? 180.f : 100.f),
      m_health(type == EnemyType::Cannibal ? 30 : 80),
      m_damage(type == EnemyType::Cannibal ? 10 : 20)
{
    const sf::Vector2u size = texture.getSize();
    m_shape.setSize(sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
    m_shape.setTexture(&texture, true);
    m_shape.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));
    m_shape.setPosition(startPosition);
}

void Enemy::update(float deltaTime, const sf::Vector2f& playerPosition)
{
    const sf::Vector2f direction = normalize(playerPosition - m_shape.getPosition());
    m_shape.move(direction * m_speed * deltaTime);

    if (direction.x != 0.f || direction.y != 0.f)
    {
        const float angle = std::atan2(direction.y, direction.x) * 57.29578f;
        m_shape.setRotation(sf::degrees(angle + 90.f));
    }
}

void Enemy::render(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

void Enemy::takeDamage(int amount)
{
    m_health -= amount;
}

sf::Vector2f Enemy::position() const
{
    return m_shape.getPosition();
}

sf::FloatRect Enemy::bounds() const
{
    const sf::FloatRect raw = m_shape.getGlobalBounds();
    return sf::FloatRect(
        sf::Vector2f(raw.position.x + 26.f, raw.position.y + 24.f),
        sf::Vector2f(raw.size.x - 52.f, raw.size.y - 48.f)
    );
}

bool Enemy::isAlive() const
{
    return m_health > 0;
}

int Enemy::damage() const
{
    return m_damage;
}

EnemyType Enemy::type() const
{
    return m_type;
}
