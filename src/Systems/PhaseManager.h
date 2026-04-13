#pragma once

#include "Entities/Enemy.h"
#include <SFML/Graphics.hpp>
#include <string>

enum class Phase
{
    Day,
    Sunset,
    Night
};

class PhaseManager
{
public:
    PhaseManager();

    void update(float deltaTime);

    Phase currentPhase() const;
    EnemyType currentEnemyType() const;
    sf::Color overlayColor() const;
    std::string label() const;

private:
    float m_timer;
};
