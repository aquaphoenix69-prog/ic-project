#include "Systems/PhaseManager.h"

PhaseManager::PhaseManager()
    : m_timer(0.f)
{
}

void PhaseManager::update(float deltaTime)
{
    m_timer += deltaTime;
}

Phase PhaseManager::currentPhase() const
{
    const int cycle = static_cast<int>(m_timer) % 42;

    if (cycle < 16)
    {
        return Phase::Day;
    }
    if (cycle < 25)
    {
        return Phase::Sunset;
    }

    return Phase::Night;
}

EnemyType PhaseManager::currentEnemyType() const
{
    return currentPhase() == Phase::Night ? EnemyType::Zombie : EnemyType::Cannibal;
}

sf::Color PhaseManager::overlayColor() const
{
    if (currentPhase() == Phase::Day)
    {
        return sf::Color(255, 255, 255, 10);
    }
    if (currentPhase() == Phase::Sunset)
    {
        return sf::Color(255, 146, 74, 56);
    }

    return sf::Color(16, 36, 84, 112);
}

std::string PhaseManager::label() const
{
    if (currentPhase() == Phase::Day)
    {
        return "Day";
    }
    if (currentPhase() == Phase::Sunset)
    {
        return "Sunset";
    }

    return "Night";
}
