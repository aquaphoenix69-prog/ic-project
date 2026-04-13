# Sujash Branch Guide

## Your role

You own the **game states and phase management** part of the project.

## Read these files first

- `src/States/MenuState.h`
- `src/States/MenuState.cpp`
- `src/States/GameplayState.h`
- `src/States/GameplayState.cpp`
- `src/States/GameOverState.h`
- `src/States/GameOverState.cpp`
- `src/Systems/PhaseManager.h`
- `src/Systems/PhaseManager.cpp`

## Your main responsibility

- control menu, gameplay, and game-over flow
- manage day, sunset, and night phase transitions
- make sure the player clearly sees what phase the game is in

## Files mainly under your side

- `src/States/*`
- `src/Systems/PhaseManager.*`

## What you should understand in the code

- how each state enters, updates, draws, and exits
- how the gameplay state connects the other gameplay systems
- how phase timing changes the feel of the game
- how transitions affect visuals and messages

## What others depend on from you

- clean switching between screens
- clear day/night progression
- gameplay flow that coordinates all systems together

## Good reading order

1. `src/Core/GameState.h`
2. `src/States/MenuState.*`
3. `src/States/GameplayState.*`
4. `src/Systems/PhaseManager.*`
5. `src/States/GameOverState.*`
