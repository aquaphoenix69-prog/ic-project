#pragma once

#include "Entities/Bullet.h"
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include <vector>

struct CollisionResult
{
    bool bulletHit;
    bool playerHit;
    int kills;
};

class CollisionSystem
{
public:
    CollisionResult resolve(Player& player, std::vector<Bullet>& bullets, std::vector<Enemy>& enemies, int& score);
};
