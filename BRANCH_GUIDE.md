# Aditya Branch Guide

## Your role

You own the **collision system and HUD/UI** part of the project.

## Read these files first

- `src/Systems/CollisionSystem.h`
- `src/Systems/CollisionSystem.cpp`
- `src/UI/HUD.h`
- `src/UI/HUD.cpp`
- `src/States/GameplayState.cpp`

## Your main responsibility

- detect player-enemy collisions
- detect bullet-enemy collisions
- update health, score, and visible gameplay information
- keep the HUD readable during play

## Files mainly under your side

- `src/Systems/CollisionSystem.*`
- `src/UI/HUD.*`

## What you should understand in the code

- how objects expose position and bounds for collision checks
- how hits change health, score, and game state
- how the HUD gets values from gameplay systems
- how gameplay state uses collision and UI together

## What others depend on from you

- correct hit detection
- correct damage handling
- accurate score, timer, and health display

## Good reading order

1. `src/Systems/CollisionSystem.h`
2. `src/Systems/CollisionSystem.cpp`
3. `src/UI/HUD.h`
4. `src/UI/HUD.cpp`
5. `src/States/GameplayState.cpp`
