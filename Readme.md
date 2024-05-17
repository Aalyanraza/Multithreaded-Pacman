Pac-Man Game Project
This project is a multi-threaded Pac-Man game implemented in C++ using the SFML library for graphics rendering. The game features Pac-Man, coins, power pellets, and enemy ghosts with specific behaviors.

Table of Contents
Introduction
Features
Installation
Usage
Files and Directories
Game Controls
Threading Details
Credits
Introduction
This project is a Pac-Man game where the player controls Pac-Man to collect coins and avoid enemy ghosts. The game uses multi-threading to handle different aspects such as enemy movement, collision detection, and rendering.

Features
Pac-Man character controlled by the player.
Coins placed in the game arena to be collected by Pac-Man.
Enemy ghosts that chase Pac-Man.
Power pellets that grant temporary invincibility to Pac-Man.
Multi-threaded architecture for handling game logic and rendering.
Installation
Clone the repository:

sh
Copy code
git clone https://github.com/your-repo/pacman-game.git
cd pacman-game
Install SFML:
Follow the instructions on the SFML website to install SFML on your system.

Build the project:

sh
Copy code
mkdir build
cd build
cmake ..
make
Usage
Run the game:

sh
Copy code
./pacman-game
Game Controls:

W or Up Arrow - Move Up
A or Left Arrow - Move Left
S or Down Arrow - Move Down
D or Right Arrow - Move Right
Enter - Exit the game
Files and Directories
src/: Contains the source code files.
game.h: Contains game-related functions and definitions.
enemy.h: Handles enemy behavior and collision detection.
collision.h: Manages collision detection logic.
menu.h: Menu-related functions and definitions.
shared_variables.h: Shared variables used across the project.
assets/: Contains image files for Pac-Man, ghosts, and other sprites.
build/: Directory for build files and the executable.
Game Controls
Pac-Man Movement:

W or Up Arrow: Move Pac-Man up.
A or Left Arrow: Move Pac-Man left.
S or Down Arrow: Move Pac-Man down.
D or Right Arrow: Move Pac-Man right.
Game Actions:

Enter: Exit the game.
Threading Details
The game uses 12 threads:

Main thread: Initializes the game and manages the main loop.
Menu/User thread: Handles user input and menu operations.
Game thread: Manages game logic and rendering.
Enemy threads: Four threads, each managing the behavior of an individual ghost.
Enemy/Pellet Collision threads: Four threads, each handling the collision detection between a specific ghost and power pellets.
User/Power Collision thread: Handles collision detection between Pac-Man and power pellets.
Credits
This project was developed as part of a multi-threaded programming course. It uses the SFML library for graphics rendering. Special thanks to the course instructors and the SFML community for their support and resources.
