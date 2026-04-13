# Survival Island Starter

This is a clean, beginner-friendly C++ starter for a 2D survival game using:

- C++17
- SFML 3.x
- CMake

## Why this stack

This project keeps the stack intentionally small so the team can learn it:

- `SFML` handles the window, drawing, input, time, text, and audio.
- `CMake` keeps the build setup clean.
- The code is split into clear folders so 5 people can work in parallel.

## Project overview

This repository is for **Survival Island: The Last Man**, a 2D survival game in full C++ using SFML and CMake. The team is splitting the work into clear modules so everyone can build in parallel and still integrate smoothly.

Before working on individual parts, everyone should first understand:

- basic `C++17` syntax and object-oriented structure
- core `SFML` basics for window, sprites, text, input, timing, and audio
- how `CMake` builds the project
- the overall game loop and how states connect the game flow

## Team responsibilities

- `Aditya` - Core Engine & State Management
  Builds the project foundation, game loop, base architecture, and core state flow so the rest of the team can plug their systems into a stable structure.
- `Yug` - Player System & Input
  Handles player movement, shooting, bullets, stamina, and player-side controls.
- `Chinmay` - Enemy System & AI
  Creates enemy types, chase behavior, and the spawn system that controls waves and difficulty growth.
- `Sujash` - Game States & Phase Management
  Works on menu, gameplay, and game-over screens, along with the day, sunset, and night phase transitions.
- `Premansh (Pompu)` - Collision System & UI/HUD
  Handles bullet-enemy and player-enemy collision logic, plus the HUD such as health, score, timer, and gameplay display elements.
- `Daksh` - Integration, Assets, Polish & Testing
  Takes care of connecting all modules, organizing assets, balancing gameplay, handling audio/visual polish, and helping with final testing and cleanup.

## What Each Person Should Study

- `Everyone first`
  Study basic C++, SFML fundamentals, CMake, and the full project flow before starting module-specific work.
- `Aditya`
  Study the game loop, state pattern, project structure, abstract/base classes, and build setup.
- `Yug`
  Study input handling, movement logic, vector math, shooting flow, and player-to-bullet interaction.
- `Chinmay`
  Study enemy data design, simple AI chase behavior, random spawning, timers, and wave progression.
- `Sujash`
  Study state transitions, timers, screen flow, menu/game-over UI behavior, and visual phase changes for day/night.
- `Premansh (Pompu)`
  Study collision detection, hit logic, health/score updates, HUD placement, and on-screen information display.
- `Daksh`
  Study asset sourcing, folder organization, audio setup, balancing, testing workflow, and final integration checks.

## Assets and non-code work

The non-coding work is also part of the project. Assets for textures, sounds, fonts, and music should be gathered and organized alongside development instead of blocking gameplay programming.

- `Daksh` should lead asset collection, integration, and polish.
- `Kenney.nl` can supply free placeholder or final game textures and sprites.
- `Google Fonts` can supply UI/title fonts.
- `Freesound` or similar free libraries can supply sound effects.
- `Incompetech`, `FreePD`, or similar free libraries can supply background music.
- Placeholder assets can be used early so code work continues even before final art and audio are ready.

## Build

This machine is already set up with:

- `MSYS2`
- `GCC (UCRT64)`
- `CMake`
- `Ninja`
- `SFML 3`

To build from PowerShell, run:

```powershell
.\build.ps1
```

To run the game:

```powershell
.\run.ps1
```

If PowerShell says scripts are disabled on your system, use these instead:

```powershell
.\build.cmd
.\run.cmd
```

## Project goal

The code here is a readable base, not a finished game. Each file is meant to be easy to extend without introducing advanced patterns too early.
