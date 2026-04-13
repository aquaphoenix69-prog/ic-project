cmake_minimum_required(VERSION 3.16)
project(SurvivalIsland LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

set(SOURCES
    src/main.cpp
    src/Core/Game.cpp
    src/States/MenuState.cpp
    src/States/GameplayState.cpp
    src/States/GameOverState.cpp
    src/Entities/Player.cpp
    src/Entities/Enemy.cpp
    src/Entities/Bullet.cpp
    src/Systems/SpawnSystem.cpp
    src/Systems/PhaseManager.cpp
    src/Systems/CollisionSystem.cpp
    src/UI/HUD.cpp
)

add_executable(SurvivalIsland ${SOURCES})

target_include_directories(SurvivalIsland PRIVATE src)

target_link_libraries(SurvivalIsland
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)
