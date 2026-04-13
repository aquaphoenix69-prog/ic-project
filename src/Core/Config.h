#pragma once

#include <string_view>

namespace Config
{
constexpr unsigned int WindowWidth = 1280;
constexpr unsigned int WindowHeight = 720;
constexpr unsigned int CameraWidth = 960;
constexpr unsigned int CameraHeight = 540;
constexpr unsigned int WorldWidth = 3200;
constexpr unsigned int WorldHeight = 2400;

constexpr std::string_view FontPath = "assets/fonts/arial.ttf";
constexpr std::string_view PlayerTexturePath = "assets/textures/player_body.png";
constexpr std::string_view PistolTexturePath = "assets/textures/pistol.png";
constexpr std::string_view AxeTexturePath = "assets/textures/axe.png";
constexpr std::string_view BulletTexturePath = "assets/textures/bullet.png";
constexpr std::string_view CannibalTexturePath = "assets/textures/cannibal.png";
constexpr std::string_view ZombieTexturePath = "assets/textures/zombie.png";
constexpr std::string_view TreeTexturePath = "assets/textures/tree.png";
constexpr std::string_view RockTexturePath = "assets/textures/rock.png";
constexpr std::string_view DayBackgroundPath = "assets/textures/island_day.png";
constexpr std::string_view SunsetBackgroundPath = "assets/textures/island_sunset.png";
constexpr std::string_view NightBackgroundPath = "assets/textures/island_night.png";
constexpr std::string_view HudPanelPath = "assets/textures/hud_panel.png";

constexpr std::string_view ShootSoundPath = "assets/sounds/shoot.wav";
constexpr std::string_view HitSoundPath = "assets/sounds/hit.wav";
constexpr std::string_view DayMusicPath = "assets/sounds/day_theme.wav";
constexpr std::string_view NightMusicPath = "assets/sounds/night_theme.wav";
}
