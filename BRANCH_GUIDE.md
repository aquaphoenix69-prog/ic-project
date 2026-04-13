# Yug Branch Guide

## Your role

You own the **core architecture and state management** part of the project.

## Read these files first

- `src/main.cpp`
- `src/Core/Game.h`
- `src/Core/Game.cpp`
- `src/Core/GameState.h`
- `src/Core/Config.h`

## Your main responsibility

- understand how the game starts
- understand how the main loop runs
- understand how states are stored and switched
- keep the project structure clean so everyone else can plug their systems in

## Files mainly under your side

- `src/Core/*`
- `src/main.cpp`

## What you should understand in the code

- how `Game` owns the window and active state
- how `handleEvent`, `update`, and `render` flow through the game
- how menu, gameplay, and game over states connect to the core loop
- how shared constants from `Config.h` affect the rest of the project

## What others depend on from you

- a stable game loop
- clean state switching
- shared configuration and base structure

## Good reading order

1. `src/main.cpp`
2. `src/Core/Game.h`
3. `src/Core/Game.cpp`
4. `src/Core/GameState.h`
5. `src/States/*`
