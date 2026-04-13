#include "Entities/Player.h"
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

Player::Player()
    : m_speed(260.f),
      m_health(100)
{
    m_position = sf::Vector2f(1600.f, 1200.f);
    m_aimDirection = sf::Vector2f(1.f, 0.f);
    m_weapon = WeaponType::Pistol;
    m_axeSwingTimer = 0.f;
}

void Player::setTextures(const sf::Texture& bodyTexture, const sf::Texture& pistolTexture, const sf::Texture& axeTexture)
{
    const sf::Vector2u bodySize = bodyTexture.getSize();
    m_bodySprite.setSize(sf::Vector2f(static_cast<float>(bodySize.x), static_cast<float>(bodySize.y)));
    m_bodySprite.setTexture(&bodyTexture, true);
    m_bodySprite.setOrigin(sf::Vector2f(bodySize.x / 2.f, bodySize.y / 2.f));

    const sf::Vector2u pistolSize = pistolTexture.getSize();
    m_pistolSprite.setSize(sf::Vector2f(static_cast<float>(pistolSize.x), static_cast<float>(pistolSize.y)));
    m_pistolSprite.setTexture(&pistolTexture, true);
    m_pistolSprite.setOrigin(sf::Vector2f(18.f, pistolSize.y / 2.f));

    const sf::Vector2u axeSize = axeTexture.getSize();
    m_axeSprite.setSize(sf::Vector2f(static_cast<float>(axeSize.x), static_cast<float>(axeSize.y)));
    m_axeSprite.setTexture(&axeTexture, true);
    m_axeSprite.setOrigin(sf::Vector2f(10.f, axeSize.y - 8.f));

    updateSpritePositions();
}

sf::Vector2f Player::update(float deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    sf::Vector2f aimInput(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        movement.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        movement.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        movement.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        movement.x += 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        aimInput.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        aimInput.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        aimInput.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        aimInput.x += 1.f;
    }

    if (aimInput.x != 0.f || aimInput.y != 0.f)
    {
        m_aimDirection = normalize(aimInput);
    }

    sf::Vector2f velocity(0.f, 0.f);
    if (movement.x != 0.f || movement.y != 0.f)
    {
        velocity = normalize(movement) * m_speed * deltaTime;
        m_position += velocity;
    }

    if (m_axeSwingTimer > 0.f)
    {
        m_axeSwingTimer -= deltaTime;
        if (m_axeSwingTimer < 0.f)
        {
            m_axeSwingTimer = 0.f;
        }
    }

    updateSpritePositions();
    return velocity;
}

void Player::render(sf::RenderWindow& window) const
{
    window.draw(m_bodySprite);
    if (m_weapon == WeaponType::Pistol)
    {
        window.draw(m_pistolSprite);
    }
    else
    {
        window.draw(m_axeSprite);
    }
}

Bullet Player::fire(const sf::Texture& bulletTexture) const
{
    const sf::Vector2f bulletPosition = m_position + (m_aimDirection * 36.f);
    return Bullet(bulletTexture, bulletPosition, m_aimDirection * 520.f);
}

void Player::takeDamage(int amount)
{
    m_health -= amount;
    if (m_health < 0)
    {
        m_health = 0;
    }
}

sf::Vector2f Player::position() const
{
    return m_position;
}

sf::Vector2f Player::aimDirection() const
{
    return m_aimDirection;
}

sf::FloatRect Player::bounds() const
{
    const sf::FloatRect raw = m_bodySprite.getGlobalBounds();
    return sf::FloatRect(
        sf::Vector2f(raw.position.x + 24.f, raw.position.y + 22.f),
        sf::Vector2f(raw.size.x - 48.f, raw.size.y - 42.f)
    );
}

sf::FloatRect Player::axeBounds() const
{
    const sf::Vector2f center = m_position + (m_aimDirection * 54.f);
    return sf::FloatRect(
        sf::Vector2f(center.x - 42.f, center.y - 42.f),
        sf::Vector2f(84.f, 84.f)
    );
}

WeaponType Player::weapon() const
{
    return m_weapon;
}

bool Player::isAxeSwinging() const
{
    return m_axeSwingTimer > 0.f;
}

int Player::health() const
{
    return m_health;
}

bool Player::isAlive() const
{
    return m_health > 0;
}

void Player::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    updateSpritePositions();
}

void Player::setWeapon(WeaponType weapon)
{
    m_weapon = weapon;
    updateSpritePositions();
}

void Player::startAxeSwing()
{
    m_weapon = WeaponType::Axe;
    m_axeSwingTimer = 0.22f;
    updateSpritePositions();
}

void Player::updateSpritePositions()
{
    m_bodySprite.setPosition(m_position);
    m_pistolSprite.setPosition(m_position + (m_aimDirection * 10.f));
    m_axeSprite.setPosition(m_position + (m_aimDirection * 28.f));

    const float angle = std::atan2(m_aimDirection.y, m_aimDirection.x) * 57.29578f;
    m_pistolSprite.setRotation(sf::degrees(angle));

    const float swingProgress = m_axeSwingTimer > 0.f ? (m_axeSwingTimer / 0.22f) : 0.f;
    const float swingOffset = m_axeSwingTimer > 0.f ? (-75.f + ((1.f - swingProgress) * 150.f)) : 28.f;
    m_axeSprite.setRotation(sf::degrees(angle + 90.f + swingOffset));
}
