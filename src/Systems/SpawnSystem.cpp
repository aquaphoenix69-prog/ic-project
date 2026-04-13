#include "Systems/SpawnSystem.h"
#include <cstdlib>
#include <cmath>

SpawnSystem::SpawnSystem()
    : m_spawnTimer(0.f),
      m_spawnDelay(2.5f)
{
}

std::optional<sf::Vector2f> SpawnSystem::update(float deltaTime, EnemyType currentType, const sf::Vector2f& playerPosition)
{
    m_spawnDelay = currentType == EnemyType::Cannibal ? 1.7f : 1.15f;
    m_spawnTimer += deltaTime;

    if (m_spawnTimer >= m_spawnDelay)
    {
        m_spawnTimer = 0.f;
        return randomSpawnPosition(playerPosition, currentType);
    }

    return std::nullopt;
}

sf::Vector2f SpawnSystem::randomSpawnPosition(const sf::Vector2f& playerPosition, EnemyType currentType) const
{
    const float distance = currentType == EnemyType::Zombie ? 720.f : 620.f;
    const float angle = static_cast<float>(std::rand() % 360) * 0.0174533f;
    return sf::Vector2f(
        playerPosition.x + (std::cos(angle) * distance),
        playerPosition.y + (std::sin(angle) * distance)
    );
}
