#pragma once

#include "Entities/Bullet.h"
#include <SFML/Graphics.hpp>

enum class WeaponType
{
    Pistol,
    Axe
};

class Player
{
public:
    Player();

    void setTextures(const sf::Texture& bodyTexture, const sf::Texture& pistolTexture, const sf::Texture& axeTexture);
    sf::Vector2f update(float deltaTime);
    void render(sf::RenderWindow& window) const;
    void setPosition(const sf::Vector2f& position);
    void setWeapon(WeaponType weapon);
    void startAxeSwing();

    Bullet fire(const sf::Texture& bulletTexture) const;
    void takeDamage(int amount);

    sf::Vector2f position() const;
    sf::Vector2f aimDirection() const;
    sf::FloatRect bounds() const;
    sf::FloatRect axeBounds() const;
    WeaponType weapon() const;
    bool isAxeSwinging() const;
    int health() const;
    bool isAlive() const;

private:
    void updateSpritePositions();

    sf::RectangleShape m_bodySprite;
    sf::RectangleShape m_pistolSprite;
    sf::RectangleShape m_axeSprite;
    sf::Vector2f m_position;
    sf::Vector2f m_aimDirection;
    WeaponType m_weapon;
    float m_axeSwingTimer;
    float m_speed;
    int m_health;
};
