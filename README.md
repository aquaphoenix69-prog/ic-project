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

## Team ownership

- `Core` and the state system: Person 1
- `Entities/Player*` and `Entities/Bullet*`: Person 2
- `Entities/Enemy*` and `Systems/SpawnSystem*`: Person 3
- `States/*` and `Systems/PhaseManager*`: Person 4
- `Systems/CollisionSystem*` and `UI/HUD*`: Person 5
- Asset collection, polish, testing, balancing: optional Person 6

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
