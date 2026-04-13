#pragma once

#include "Core/GameState.h"
#include "Entities/Bullet.h"
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PhaseManager.h"
#include "Systems/SpawnSystem.h"
#include "UI/HUD.h"
#include <SFML/Audio.hpp>
#include <array>
#include <vector>

struct WorldObstacle
{
    sf::RectangleShape sprite;
    sf::FloatRect collider;
};

class GameplayState : public GameState
{
public:
    GameplayState();

    void handleEvent(Game& game, const sf::Event& event) override;
    void update(Game& game, float deltaTime) override;
    void render(Game& game) override;

private:
    bool isLandPoint(const sf::Vector2f& point) const;
    bool isRectInsideLand(const sf::FloatRect& rect) const;
    bool collidesWithObstacle(const sf::FloatRect& rect) const;
    void buildWorldObstacles();
    void clampViewToWorld(sf::View& view) const;
    void updateMusicForPhase();
    const sf::Texture& enemyTextureForPhase() const;
    const sf::RectangleShape& backgroundForPhase() const;

    sf::Texture m_playerTexture;
    sf::Texture m_pistolTexture;
    sf::Texture m_axeTexture;
    sf::Texture m_bulletTexture;
    sf::Texture m_cannibalTexture;
    sf::Texture m_zombieTexture;
    sf::Texture m_treeTexture;
    sf::Texture m_rockTexture;
    sf::Texture m_dayBackgroundTexture;
    sf::Texture m_sunsetBackgroundTexture;
    sf::Texture m_nightBackgroundTexture;
    sf::RectangleShape m_dayBackgroundSprite;
    sf::RectangleShape m_sunsetBackgroundSprite;
    sf::RectangleShape m_nightBackgroundSprite;
    sf::RectangleShape m_phaseOverlay;
    sf::View m_worldView;
    std::vector<WorldObstacle> m_obstacles;
    sf::SoundBuffer m_shootBuffer;
    sf::SoundBuffer m_hitBuffer;
    sf::Sound m_shootSound;
    sf::Sound m_hitSound;
    sf::Music m_dayMusic;
    sf::Music m_nightMusic;
    bool m_playingNightMusic;
    bool m_axeHitThisSwing;
    Player m_player;
    std::vector<Bullet> m_bullets;
    std::vector<Enemy> m_enemies;
    SpawnSystem m_spawnSystem;
    PhaseManager m_phaseManager;
    CollisionSystem m_collisionSystem;
    HUD m_hud;
    int m_score;
    float m_survivalTime;
};
