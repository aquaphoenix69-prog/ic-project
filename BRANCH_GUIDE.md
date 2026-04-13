# Daksh Branch Guide

## Your role

You own the **enemy AI and spawn system** part of the project.

## Read these files first

- `src/Entities/Enemy.h`
- `src/Entities/Enemy.cpp`
- `src/Systems/SpawnSystem.h`
- `src/Systems/SpawnSystem.cpp`
- `src/States/GameplayState.cpp`

## Your main responsibility

- create enemy behavior
- make enemies chase the player
- spawn enemies at useful times and positions
- help control difficulty through enemy timing and waves

## Files mainly under your side

- `src/Entities/Enemy.*`
- `src/Systems/SpawnSystem.*`

## What you should understand in the code

- how enemy stats are stored
- how enemies move toward the player
- how the spawn system creates and manages active enemies
- how gameplay state reads and updates enemy data

## What others depend on from you

- active enemy list for collision
- balanced enemy speed and behavior
- stable spawn timing for gameplay pacing

## Good reading order

1. `src/Entities/Enemy.h`
2. `src/Entities/Enemy.cpp`
3. `src/Systems/SpawnSystem.h`
4. `src/Systems/SpawnSystem.cpp`
5. `src/States/GameplayState.cpp`
