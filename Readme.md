# Pac-Man Game Project

This project is a multi-threaded Pac-Man game implemented in C++ using the SFML library for graphics rendering. The game features Pac-Man, coins, power pellets, and enemy ghosts with specific behaviors.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Files and Directories](#files-and-directories)
- [Game Controls](#game-controls)
- [Threading Details](#threading-details)
- [Credits](#credits)

## Introduction

This project is a Pac-Man game where the player controls Pac-Man to collect coins and avoid enemy ghosts. The game uses multi-threading to handle different aspects such as enemy movement, collision detection, and rendering.

## Features

- Pac-Man character controlled by the player.
- Coins placed in the game arena to be collected by Pac-Man.
- Enemy ghosts that chase Pac-Man.
- Power pellets that grant temporary invincibility to Pac-Man.
- Multi-threaded architecture for handling game logic and rendering.

## Installation

### Install SFML:
Follow the instructions on the [SFML website](https://www.sfml-dev.org/download.php) to install SFML on your system.

### Build the project:
```sh
mkdir build
cd build
cmake ..
make
