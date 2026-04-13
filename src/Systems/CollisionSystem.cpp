#include "Systems/CollisionSystem.h"

CollisionResult CollisionSystem::resolve(Player& player, std::vector<Bullet>& bullets, std::vector<Enemy>& enemies, int& score)
{
    CollisionResult result { false, false, 0 };

    for (Bullet& bullet : bullets)
    {
        if (!bullet.isAlive())
        {
            continue;
        }

        for (Enemy& enemy : enemies)
        {
            if (!enemy.isAlive())
            {
                continue;
            }

            if (bullet.bounds().findIntersection(enemy.bounds()).has_value())
            {
                bullet.destroy();
                enemy.takeDamage(25);
                result.bulletHit = true;

                if (!enemy.isAlive())
                {
                    score += 10;
                    result.kills += 1;
                }

                break;
            }
        }
    }

    for (Enemy& enemy : enemies)
    {
        if (enemy.isAlive() && enemy.bounds().findIntersection(player.bounds()).has_value())
        {
            player.takeDamage(enemy.damage());
            enemy.takeDamage(999);
            result.playerHit = true;
        }
    }

    return result;
}
