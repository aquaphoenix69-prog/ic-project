#pragma once

#include "Entities/Enemy.h"
#include <optional>

class SpawnSystem
{
public:
    SpawnSystem();

    std::optional<sf::Vector2f> update(float deltaTime, EnemyType currentType, const sf::Vector2f& playerPosition);

private:
    sf::Vector2f randomSpawnPosition(const sf::Vector2f& playerPosition, EnemyType currentType) const;

    float m_spawnTimer;
    float m_spawnDelay;
};
