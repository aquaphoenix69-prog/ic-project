# Chinmay Branch Guide

## Your role

You own the **player system and keyboard/input side** of the project.

## Read these files first

- `src/Entities/Player.h`
- `src/Entities/Player.cpp`
- `src/Entities/Bullet.h`
- `src/Entities/Bullet.cpp`
- `src/States/GameplayState.cpp`

## Your main responsibility

- handle keyboard movement
- handle player shooting
- manage bullets and their movement
- keep player controls responsive and easy to tune

## Files mainly under your side

- `src/Entities/Player.*`
- `src/Entities/Bullet.*`

## What you should understand in the code

- how the player reads keyboard input
- how movement speed and stamina are updated
- how bullets are created, updated, and removed
- how gameplay state uses the player object

## What others depend on from you

- player position for enemy AI
- bullets for collision checks
- reliable movement and shooting behavior

## Good reading order

1. `src/Entities/Player.h`
2. `src/Entities/Player.cpp`
3. `src/Entities/Bullet.h`
4. `src/Entities/Bullet.cpp`
5. `src/States/GameplayState.cpp`
