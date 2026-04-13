# Team Guide

## Basic study for everyone

Every person should first study these basics:

1. C++ basics: classes, header/source files, vectors, references, `const`
2. SFML basics: window, event loop, shapes, text, keyboard input, clock
3. CMake basics: how the project builds
4. Game loop basics: `handleEvent`, `update`, `render`
5. Git basics if you use version control

## Minimal stack for the whole project

- Language: C++17
- Graphics, window, input, time, audio: SFML 3
- Build system: CMake

Keep it minimal. Do not add new libraries unless the whole team agrees they are really needed.

## Person 1: Core Engine and State Flow

Study after basics:

- How the main game loop works
- How a base state interface works
- How to switch from menu to gameplay to game over

Own these files:

- `src/Core/*`

Deliver:

- Window setup
- State switching
- Shared values like window size and common constants

## Person 2: Player and Bullets

Study after basics:

- Keyboard input
- 2D movement
- Simple shooting logic
- Basic cooldowns and stamina timers

Own these files:

- `src/Entities/Player.*`
- `src/Entities/Bullet.*`

Deliver:

- Player movement
- Player shooting
- Bullet update and draw

## Person 3: Enemies and Spawning

Study after basics:

- Position and direction math
- Chasing the player
- Managing a list of enemies
- Spawn timers and simple wave logic

Own these files:

- `src/Entities/Enemy.*`
- `src/Systems/SpawnSystem.*`

Deliver:

- Enemy types
- Enemy movement toward the player
- Spawning at screen edges

## Person 4: Screens and Day/Night Flow

Study after basics:

- Menu screens
- Game over screens
- Phase timers
- Changing colors and messages based on time

Own these files:

- `src/States/*`
- `src/Systems/PhaseManager.*`

Deliver:

- Menu screen
- Gameplay screen flow
- Game over screen
- Day, sunset, and night timing

## Person 5: Collision and HUD

Study after basics:

- Rectangle collision
- Damage rules
- Health display
- Score and timer text

Own these files:

- `src/Systems/CollisionSystem.*`
- `src/UI/HUD.*`

Deliver:

- Bullet-enemy collision
- Enemy-player collision
- Health bar
- Score text
- Timer text

## Optional Person 6: Assets, Polish, Testing

Study after basics:

- Asset folder organization
- Font and texture loading
- Sound volume balancing
- Testing the full game flow

Own:

- Asset folder setup
- Sound/music setup later
- Build checking and final cleanup

Deliver:

- Placeholder assets first
- Final asset replacement later
- Final playtesting notes
