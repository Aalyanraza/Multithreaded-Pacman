#ifndef GAME_H
#define GAME_H


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "shared_variables.h"
#include "user.h"
#include "enemy.h"
using namespace std;
using namespace sf;

// Wall coordinates
void initWalls() 
{
    // 1st inner box
        // 2 perpendicular walls to long horizontal walls (|)------------------(|)
    wallcoordinates wall1 = {50, 50, 3, 100};
    wallVector.push_back(wall1);

    wallcoordinates wall2 = {1030, 50, 3, 100};
    wallVector.push_back(wall2);

    wallcoordinates wall9 = {50, 750, 3, -100};
    wallVector.push_back(wall9);

    wallcoordinates wall10 = {1029, 750, 3, -100};
    wallVector.push_back(wall10);

        // 2 long horizontal walls |(------------------)|
    wallcoordinates wall3 = {50, 50, 980, 3};
    wallVector.push_back(wall3);

    wallcoordinates wall4 = {50, 750, 980, 3};
    wallVector.push_back(wall4);

        // Vertical walls in the middle
    wallcoordinates wall11 = {50, 200, 3, 400};
    wallVector.push_back(wall11);

    wallcoordinates wall12 = {1030, 200, 3, 400};
    wallVector.push_back(wall12);

    // box in the middle
    wallcoordinates wall5 = {440, 300, 3, 200};
    wallVector.push_back(wall5);

    wallcoordinates wall6 = {640, 300, 3, 200};
    wallVector.push_back(wall6);

    wallcoordinates wall7 = {440, 300, 75, 3};
    wallVector.push_back(wall7);

    wallcoordinates wall13 = {565, 300, 75, 3};
    wallVector.push_back(wall13);

    wallcoordinates wall8 = {440, 500, 200, 3};
    wallVector.push_back(wall8);

    // 2nd inner box
        // 2 perpendicular walls to long horizontal walls (|)------------------(|)
    wallcoordinates wall14 = {150, 100, 100, 3};
    wallVector.push_back(wall14);

    wallcoordinates wall15 = {150, 700, 100, 3};
    wallVector.push_back(wall15);    

    wallcoordinates wall16 = {930, 100, -100, 3};
    wallVector.push_back(wall16);

    wallcoordinates wall17 = {930, 700, -100, 3};
    wallVector.push_back(wall17);

    //     // 2 long vertical walls |(------------------)|
    wallcoordinates wall18 = {150, 100, 3, 600};
    wallVector.push_back(wall18);

    wallcoordinates wall19 = {930, 100, 3, 600};
    wallVector.push_back(wall19);

        // Horizontal walls in the middle
    wallcoordinates wall20 = {350, 100, 380, 03};
    wallVector.push_back(wall20);

    wallcoordinates wall21 = {350, 700, 380, 03};
    wallVector.push_back(wall21);

    // 3rd Box
        // 1st vertex
    wallcoordinates wall22 = {250, 200, 240, 3};
    wallVector.push_back(wall22);
    wallcoordinates wall23 = {250, 200, 3, 150};    
    wallVector.push_back(wall23);

        // 2nd vertex
    wallcoordinates wall24 = {250, 600, 3, -150};
    wallVector.push_back(wall24);
    wallcoordinates wall25 = {250, 600, 240, 3};
    wallVector.push_back(wall25);

        // 3rd vertex
    wallcoordinates wall26 = {830, 200, 3, 150};
    wallVector.push_back(wall26);
    wallcoordinates wall27 = {830, 200, -240, 3};
    wallVector.push_back(wall27);

        // 4th vertex
    wallcoordinates wall28 = {830, 600, 3, -150};
    wallVector.push_back(wall28);
    wallcoordinates wall29 = {830, 600, -240, 3};
    wallVector.push_back(wall29);


    // Boundaries
    wallcoordinates cornerWall1 = {1, 1, 1080, 5};
    wallVector.push_back(cornerWall1);

    wallcoordinates cornerWall2 = {1, 1, 5, 800};
    wallVector.push_back(cornerWall2);

    wallcoordinates cornerWall3 = {1, 795, 1080, 5};
    wallVector.push_back(cornerWall3);

    wallcoordinates cornerWall4 = {1075, 1, 5, 800};
    wallVector.push_back(cornerWall4);
}

void drawWalls(RenderWindow& window) {
    for (const auto& coord : wallVector) 
    {
        RectangleShape wall(Vector2f(coord.width, coord.height));
        wall.setPosition(coord.x, coord.y);
        wall.setFillColor(Color::Blue);
        window.draw(wall);
    }
}



void* game_thread(void *arg)
{
    // Create RenderWindow here
    RenderWindow window(VideoMode(1080, 800), "Game");
    window.setPosition(sf::Vector2i(100, 100));
    window.setFramerateLimit(60);

    initWalls();

    // Load pacman image
    Texture pacmanTexture;
    if (!pacmanTexture.loadFromFile("pacman.jpg")) {
        cerr << "Failed to load pacman.jpg" << endl;
        pthread_exit(NULL);
    }
    Sprite pacmanSprite(pacmanTexture);
    pacmanSprite.setScale(0.1, 0.1);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

        // Set position of pacman sprite to userCoordinates
        pacmanSprite.setPosition(userCoordinates.x, userCoordinates.y);

        drawWalls(window);
        window.draw(pacmanSprite);
        window.display();

        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            window.close();
        }
    }
    pthread_exit(NULL);
}
#endif