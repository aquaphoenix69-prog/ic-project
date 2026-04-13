#include "Entities/Bullet.h"
#include "Core/Config.h"
#include <cmath>

Bullet::Bullet(const sf::Texture& texture, const sf::Vector2f& startPosition, const sf::Vector2f& velocity)
    : m_velocity(velocity),
      m_alive(true)
{
    const sf::Vector2u size = texture.getSize();
    m_shape.setSize(sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
    m_shape.setTexture(&texture, true);
    m_shape.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));
    m_shape.setPosition(startPosition);

    const float angle = std::atan2(m_velocity.y, m_velocity.x) * 57.29578f;
    m_shape.setRotation(sf::degrees(angle));
}

void Bullet::update(float deltaTime)
{
    m_shape.move(m_velocity * deltaTime);

    const sf::Vector2f position = m_shape.getPosition();
    if (position.x < -80.f ||
        position.x > static_cast<float>(Config::WorldWidth) + 80.f ||
        position.y < -80.f ||
        position.y > static_cast<float>(Config::WorldHeight) + 80.f)
    {
        m_alive = false;
    }
}

void Bullet::render(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

void Bullet::destroy()
{
    m_alive = false;
}

sf::Vector2f Bullet::position() const
{
    return m_shape.getPosition();
}

sf::FloatRect Bullet::bounds() const
{
    return m_shape.getGlobalBounds();
}

bool Bullet::isAlive() const
{
    return m_alive;
}
