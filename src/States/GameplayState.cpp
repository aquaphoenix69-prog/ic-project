#include "Core/Config.h"
#include "States/GameplayState.h"
#include "Core/Game.h"
#include "States/GameOverState.h"
#include <algorithm>
#include <cmath>

namespace
{
bool intersects(const sf::FloatRect& a, const sf::FloatRect& b)
{
    return a.findIntersection(b).has_value();
}
}

GameplayState::GameplayState()
    : m_shootSound(m_shootBuffer),
      m_hitSound(m_hitBuffer),
      m_playingNightMusic(false),
      m_axeHitThisSwing(false),
      m_score(0),
      m_survivalTime(0.f)
{
    const bool playerLoaded = m_playerTexture.loadFromFile(Config::PlayerTexturePath.data());
    const bool pistolLoaded = m_pistolTexture.loadFromFile(Config::PistolTexturePath.data());
    const bool axeLoaded = m_axeTexture.loadFromFile(Config::AxeTexturePath.data());
    const bool bulletLoaded = m_bulletTexture.loadFromFile(Config::BulletTexturePath.data());
    const bool cannibalLoaded = m_cannibalTexture.loadFromFile(Config::CannibalTexturePath.data());
    const bool zombieLoaded = m_zombieTexture.loadFromFile(Config::ZombieTexturePath.data());
    const bool treeLoaded = m_treeTexture.loadFromFile(Config::TreeTexturePath.data());
    const bool rockLoaded = m_rockTexture.loadFromFile(Config::RockTexturePath.data());
    const bool dayLoaded = m_dayBackgroundTexture.loadFromFile(Config::DayBackgroundPath.data());
    const bool sunsetLoaded = m_sunsetBackgroundTexture.loadFromFile(Config::SunsetBackgroundPath.data());
    const bool nightLoaded = m_nightBackgroundTexture.loadFromFile(Config::NightBackgroundPath.data());
    (void)playerLoaded;
    (void)pistolLoaded;
    (void)axeLoaded;
    (void)bulletLoaded;
    (void)cannibalLoaded;
    (void)zombieLoaded;
    (void)treeLoaded;
    (void)rockLoaded;
    (void)dayLoaded;
    (void)sunsetLoaded;
    (void)nightLoaded;

    m_playerTexture.setSmooth(false);
    m_pistolTexture.setSmooth(false);
    m_axeTexture.setSmooth(false);
    m_bulletTexture.setSmooth(false);
    m_cannibalTexture.setSmooth(false);
    m_zombieTexture.setSmooth(false);
    m_treeTexture.setSmooth(false);
    m_rockTexture.setSmooth(false);
    m_dayBackgroundTexture.setSmooth(false);
    m_sunsetBackgroundTexture.setSmooth(false);
    m_nightBackgroundTexture.setSmooth(false);

    m_dayBackgroundSprite.setSize(sf::Vector2f(static_cast<float>(Config::WorldWidth), static_cast<float>(Config::WorldHeight)));
    m_sunsetBackgroundSprite.setSize(sf::Vector2f(static_cast<float>(Config::WorldWidth), static_cast<float>(Config::WorldHeight)));
    m_nightBackgroundSprite.setSize(sf::Vector2f(static_cast<float>(Config::WorldWidth), static_cast<float>(Config::WorldHeight)));
    m_dayBackgroundSprite.setTexture(&m_dayBackgroundTexture, true);
    m_sunsetBackgroundSprite.setTexture(&m_sunsetBackgroundTexture, true);
    m_nightBackgroundSprite.setTexture(&m_nightBackgroundTexture, true);

    m_player.setTextures(m_playerTexture, m_pistolTexture, m_axeTexture);
    buildWorldObstacles();

    m_phaseOverlay.setSize(sf::Vector2f(static_cast<float>(Config::WindowWidth), static_cast<float>(Config::WindowHeight)));
    m_worldView = sf::View(
        sf::FloatRect(
            sf::Vector2f(0.f, 0.f),
            sf::Vector2f(static_cast<float>(Config::CameraWidth), static_cast<float>(Config::CameraHeight))
        )
    );
    m_worldView.setCenter(m_player.position());

    const bool shootLoaded = m_shootBuffer.loadFromFile(Config::ShootSoundPath.data());
    const bool hitLoaded = m_hitBuffer.loadFromFile(Config::HitSoundPath.data());
    (void)shootLoaded;
    (void)hitLoaded;
    m_shootSound.setVolume(42.f);
    m_hitSound.setVolume(48.f);

    const bool dayMusicLoaded = m_dayMusic.openFromFile(Config::DayMusicPath.data());
    const bool nightMusicLoaded = m_nightMusic.openFromFile(Config::NightMusicPath.data());
    (void)dayMusicLoaded;
    (void)nightMusicLoaded;
    m_dayMusic.setLooping(true);
    m_nightMusic.setLooping(true);
    m_dayMusic.setVolume(34.f);
    m_nightMusic.setVolume(26.f);
    m_dayMusic.play();
}

void GameplayState::handleEvent(Game&, const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Num1)
        {
            m_player.setWeapon(WeaponType::Pistol);
        }
        if (keyPressed->code == sf::Keyboard::Key::Num2)
        {
            m_player.setWeapon(WeaponType::Axe);
        }
        if (keyPressed->code == sf::Keyboard::Key::Space)
        {
            if (m_player.weapon() == WeaponType::Pistol)
            {
                m_bullets.push_back(m_player.fire(m_bulletTexture));
                m_shootSound.play();
            }
            else
            {
                m_player.startAxeSwing();
                m_axeHitThisSwing = false;
            }
        }
    }
}

void GameplayState::update(Game& game, float deltaTime)
{
    m_survivalTime += deltaTime;

    const sf::Vector2f previousPosition = m_player.position();
    m_player.update(deltaTime);
    if (!isRectInsideLand(m_player.bounds()) || collidesWithObstacle(m_player.bounds()))
    {
        m_player.setPosition(previousPosition);
    }

    m_phaseManager.update(deltaTime);
    updateMusicForPhase();

    const std::optional<sf::Vector2f> spawnPosition = m_spawnSystem.update(deltaTime, m_phaseManager.currentEnemyType(), m_player.position());
    if (spawnPosition.has_value() && isLandPoint(*spawnPosition))
    {
        m_enemies.emplace_back(m_phaseManager.currentEnemyType(), enemyTextureForPhase(), *spawnPosition);
    }

    for (Bullet& bullet : m_bullets)
    {
        bullet.update(deltaTime);
    }

    for (Enemy& enemy : m_enemies)
    {
        const sf::Vector2f previousEnemyPosition = enemy.position();
        enemy.update(deltaTime, m_player.position());
        if (!isRectInsideLand(enemy.bounds()) || collidesWithObstacle(enemy.bounds()))
        {
            enemy = Enemy(enemy.type(), enemyTextureForPhase(), previousEnemyPosition);
        }
    }

    if (m_player.isAxeSwinging() && !m_axeHitThisSwing)
    {
        for (Enemy& enemy : m_enemies)
        {
            if (enemy.isAlive() && intersects(m_player.axeBounds(), enemy.bounds()))
            {
                enemy.takeDamage(55);
                m_hitSound.play();
                if (!enemy.isAlive())
                {
                    m_score += 10;
                }
            }
        }

        m_axeHitThisSwing = true;
    }

    const CollisionResult collision = m_collisionSystem.resolve(m_player, m_bullets, m_enemies, m_score);
    if (collision.bulletHit || collision.playerHit)
    {
        m_hitSound.play();
    }

    m_hud.update(m_player.health(), m_score, static_cast<int>(m_enemies.size()), m_phaseManager.label(), m_survivalTime);

    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& bullet) { return !bullet.isAlive(); }),
        m_bullets.end()
    );

    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(), [](const Enemy& enemy) { return !enemy.isAlive(); }),
        m_enemies.end()
    );

    if (!m_player.isAlive())
    {
        game.changeState(std::make_unique<GameOverState>(m_score, m_survivalTime));
    }

    m_worldView.setCenter(m_player.position());
    clampViewToWorld(m_worldView);
}

void GameplayState::render(Game& game)
{
    game.window().setView(m_worldView);
    game.window().draw(backgroundForPhase());

    for (const WorldObstacle& obstacle : m_obstacles)
    {
        game.window().draw(obstacle.sprite);
    }

    m_player.render(game.window());

    for (const Bullet& bullet : m_bullets)
    {
        bullet.render(game.window());
    }

    for (const Enemy& enemy : m_enemies)
    {
        enemy.render(game.window());
    }

    m_phaseOverlay.setPosition(m_worldView.getCenter() - (m_worldView.getSize() / 2.f));
    m_phaseOverlay.setFillColor(m_phaseManager.overlayColor());
    game.window().draw(m_phaseOverlay);

    game.window().setView(game.window().getDefaultView());
    m_hud.render(game.window());
}

void GameplayState::updateMusicForPhase()
{
    const bool shouldPlayNight = m_phaseManager.currentPhase() == Phase::Night;
    if (shouldPlayNight == m_playingNightMusic)
    {
        return;
    }

    m_playingNightMusic = shouldPlayNight;
    if (shouldPlayNight)
    {
        m_dayMusic.stop();
        m_nightMusic.play();
    }
    else
    {
        m_nightMusic.stop();
        m_dayMusic.play();
    }
}

const sf::Texture& GameplayState::enemyTextureForPhase() const
{
    return m_phaseManager.currentEnemyType() == EnemyType::Zombie ? m_zombieTexture : m_cannibalTexture;
}

const sf::RectangleShape& GameplayState::backgroundForPhase() const
{
    if (m_phaseManager.currentPhase() == Phase::Day)
    {
        return m_dayBackgroundSprite;
    }
    if (m_phaseManager.currentPhase() == Phase::Sunset)
    {
        return m_sunsetBackgroundSprite;
    }

    return m_nightBackgroundSprite;
}

bool GameplayState::isLandPoint(const sf::Vector2f& point) const
{
    const std::array<sf::FloatRect, 5> landBlocks {
        sf::FloatRect(sf::Vector2f(480.f, 430.f), sf::Vector2f(2240.f, 240.f)),
        sf::FloatRect(sf::Vector2f(320.f, 670.f), sf::Vector2f(2580.f, 410.f)),
        sf::FloatRect(sf::Vector2f(420.f, 1080.f), sf::Vector2f(2380.f, 440.f)),
        sf::FloatRect(sf::Vector2f(640.f, 1520.f), sf::Vector2f(1900.f, 360.f)),
        sf::FloatRect(sf::Vector2f(980.f, 1880.f), sf::Vector2f(1180.f, 170.f))
    };

    for (const sf::FloatRect& block : landBlocks)
    {
        if (block.contains(point))
        {
            return true;
        }
    }

    return false;
}

bool GameplayState::isRectInsideLand(const sf::FloatRect& rect) const
{
    const std::array<sf::Vector2f, 4> points {
        sf::Vector2f(rect.position.x, rect.position.y),
        sf::Vector2f(rect.position.x + rect.size.x, rect.position.y),
        sf::Vector2f(rect.position.x, rect.position.y + rect.size.y),
        sf::Vector2f(rect.position.x + rect.size.x, rect.position.y + rect.size.y)
    };

    for (const sf::Vector2f& point : points)
    {
        if (!isLandPoint(point))
        {
            return false;
        }
    }

    return true;
}

bool GameplayState::collidesWithObstacle(const sf::FloatRect& rect) const
{
    for (const WorldObstacle& obstacle : m_obstacles)
    {
        if (intersects(rect, obstacle.collider))
        {
            return true;
        }
    }

    return false;
}

void GameplayState::buildWorldObstacles()
{
    struct ObstacleSpec
    {
        bool isTree;
        sf::Vector2f position;
        sf::Vector2f size;
    };

    const std::array<ObstacleSpec, 14> specs {
        ObstacleSpec { true,  { 1180.f, 920.f },  { 112.f, 140.f } },
        ObstacleSpec { true,  { 1680.f, 780.f },  { 112.f, 140.f } },
        ObstacleSpec { true,  { 2140.f, 1080.f }, { 112.f, 140.f } },
        ObstacleSpec { true,  { 980.f, 1450.f },  { 112.f, 140.f } },
        ObstacleSpec { true,  { 1900.f, 1580.f }, { 112.f, 140.f } },
        ObstacleSpec { true,  { 2350.f, 1650.f }, { 112.f, 140.f } },
        ObstacleSpec { true,  { 720.f, 1260.f },  { 112.f, 140.f } },
        ObstacleSpec { false, { 1420.f, 1230.f }, { 128.f, 88.f } },
        ObstacleSpec { false, { 860.f, 1140.f },  { 128.f, 88.f } },
        ObstacleSpec { false, { 2270.f, 1320.f }, { 128.f, 88.f } },
        ObstacleSpec { false, { 1560.f, 1820.f }, { 128.f, 88.f } },
        ObstacleSpec { false, { 1200.f, 1680.f }, { 128.f, 88.f } },
        ObstacleSpec { false, { 2520.f, 1040.f }, { 128.f, 88.f } },
        ObstacleSpec { false, { 1840.f, 1020.f }, { 128.f, 88.f } }
    };

    m_obstacles.clear();
    for (const ObstacleSpec& spec : specs)
    {
        WorldObstacle obstacle;
        obstacle.sprite.setSize(spec.size);
        obstacle.sprite.setOrigin(spec.size / 2.f);
        obstacle.sprite.setPosition(spec.position);
        obstacle.sprite.setTexture(spec.isTree ? &m_treeTexture : &m_rockTexture, true);
        if (spec.isTree)
        {
            obstacle.collider = sf::FloatRect(
                sf::Vector2f(spec.position.x - 13.f, spec.position.y + 22.f),
                sf::Vector2f(26.f, 34.f)
            );
        }
        else
        {
            obstacle.collider = sf::FloatRect(
                sf::Vector2f(spec.position.x - 40.f, spec.position.y - 12.f),
                sf::Vector2f(80.f, 36.f)
            );
        }
        m_obstacles.push_back(obstacle);
    }
}

void GameplayState::clampViewToWorld(sf::View& view) const
{
    sf::Vector2f center = view.getCenter();
    const sf::Vector2f half = view.getSize() / 2.f;

    if (center.x < half.x)
    {
        center.x = half.x;
    }
    if (center.y < half.y)
    {
        center.y = half.y;
    }
    if (center.x > static_cast<float>(Config::WorldWidth) - half.x)
    {
        center.x = static_cast<float>(Config::WorldWidth) - half.x;
    }
    if (center.y > static_cast<float>(Config::WorldHeight) - half.y)
    {
        center.y = static_cast<float>(Config::WorldHeight) - half.y;
    }

    view.setCenter(center);
}
