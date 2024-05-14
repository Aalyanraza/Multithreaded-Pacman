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

bool isInsideWall(float x, float y) 
{
    for (const auto& wall : wallVector) 
    {
        Vector2f position = wall.getPosition();
        Vector2f size = wall.getSize();
        if (x >= position.x && x <= (position.x + size.x) && y >= position.y && y <= (position.y + size.y)) 
            return true;
    }
    return false;
}

void initCoins() 
{
    for (int i = 20; i < 1080; i += 49) 
        for (int j = 20; j < 790; j += 50) 
        {
            if (!isInsideWall(i, j) && !isInsideWall(i + 16, j + 18) &&  !isInsideWall(i + 16, j) && !isInsideWall(i, j + 18))
                if  (!( i < 640 && i > 440 && j < 500 && j > 300) )
                {
                    // cout<<"Coin at: "<<i<<" "<<j<<endl;
                    // Create a new Sprite for each coin
                    Sprite coinSprite;
                    coinSprite.setTexture(coinTexture);
                    coinSprite.setScale(0.05, 0.05);

                    coins.push_back(Coin(i, j, coinSprite));

                }
        }
    // int i=1;
    // for (auto& coin : coins) 
    // {
    //     cout << i++ <<". Position: X = " << coin.sprite.getPosition().x << ", Y = " << coin.sprite.getPosition().x << endl;
    // }

}

void initWalls()
{
    // 1st inner box
        // 4 perpendicular walls to long horizontal walls (|)------------------(|)
    RectangleShape wall1(Vector2f(3, 100));
    wall1.setPosition(50, 50);
    wallVector.push_back(wall1);

    RectangleShape wall2(Vector2f(3, 100));
    wall2.setPosition(1030, 50);
    wallVector.push_back(wall2);

    RectangleShape wall9(Vector2f(3, -100));
    wall9.setPosition(50, 750);
    wallVector.push_back(wall9);

    RectangleShape wall10(Vector2f(3, -100));
    wall10.setPosition(1029, 750);
    wallVector.push_back(wall10);

    // 2 long horizontal walls |(------------------)|
    RectangleShape wall3(Vector2f(980, 3));
    wall3.setPosition(50, 50);
    wallVector.push_back(wall3);

    RectangleShape wall4(Vector2f(980, 3));
    wall4.setPosition(50, 750);
    wallVector.push_back(wall4);

    // Vertical walls in the middle
    RectangleShape wall11(Vector2f(3, 400));
    wall11.setPosition(50, 200);
    wallVector.push_back(wall11);

    RectangleShape wall12(Vector2f(3, 400));
    wall12.setPosition(1030, 200);
    wallVector.push_back(wall12);

    // box in the middle
    RectangleShape wall5(Vector2f(3, 200));
    wall5.setPosition(440, 300);
    wallVector.push_back(wall5);

    RectangleShape wall6(Vector2f(3, 200));
    wall6.setPosition(640, 300);
    wallVector.push_back(wall6);

    RectangleShape wall7(Vector2f(75, 3));
    wall7.setPosition(440, 300);
    wallVector.push_back(wall7);

    RectangleShape wall13(Vector2f(75, 3));
    wall13.setPosition(565, 300);
    wallVector.push_back(wall13);

    RectangleShape wall8(Vector2f(200, 3));
    wall8.setPosition(440, 500);
    wallVector.push_back(wall8);

    // 2nd inner box
    // 2 perpendicular walls to long horizontal walls (|)------------------(|)
    RectangleShape wall14(Vector2f(100, 3));
    wall14.setPosition(150, 100);
    wallVector.push_back(wall14);

    RectangleShape wall15(Vector2f(100, 3));
    wall15.setPosition(150, 700);
    wallVector.push_back(wall15);

    RectangleShape wall16(Vector2f(-100, 3));
    wall16.setPosition(930, 100);
    wallVector.push_back(wall16);

    RectangleShape wall17(Vector2f(-100, 3));
    wall17.setPosition(930, 700);
    wallVector.push_back(wall17);

    // 2 long vertical walls |(------------------)|
    RectangleShape wall18(Vector2f(3, 600));
    wall18.setPosition(150, 100);
    wallVector.push_back(wall18);

    RectangleShape wall19(Vector2f(3, 600));
    wall19.setPosition(930, 100);
    wallVector.push_back(wall19);

    // Horizontal walls in the middle
    RectangleShape wall20(Vector2f(380, 3));
    wall20.setPosition(350, 100);
    wallVector.push_back(wall20);

    RectangleShape wall21(Vector2f(380, 3));
    wall21.setPosition(350, 700);
    wallVector.push_back(wall21);

    // 3rd Box
    // 1st vertex
    RectangleShape wall22(Vector2f(240, 3));
    wall22.setPosition(250, 200);
    wallVector.push_back(wall22);
    RectangleShape wall23(Vector2f(3, 150));
    wall23.setPosition(250, 200);
    wallVector.push_back(wall23);

    // 2nd vertex
    RectangleShape wall24(Vector2f(3, -150));
    wall24.setPosition(250, 600);
    wallVector.push_back(wall24);
    RectangleShape wall25(Vector2f(240, 3));
    wall25.setPosition(250, 600);
    wallVector.push_back(wall25);

    // 3rd vertex
    RectangleShape wall26(Vector2f(3, 150));
    wall26.setPosition(830, 200);
    wallVector.push_back(wall26);
    RectangleShape wall27(Vector2f(-240, 3));
    wall27.setPosition(830, 200);
    wallVector.push_back(wall27);

    // 4th vertex
    RectangleShape wall28(Vector2f(3, -150));
    wall28.setPosition(830, 600);
    wallVector.push_back(wall28);
    RectangleShape wall29(Vector2f(-240, 3));
    wall29.setPosition(830, 600);
    wallVector.push_back(wall29);

    // Boundaries
    RectangleShape cornerWall1(Vector2f(1080, 5));
    cornerWall1.setPosition(1, 1);
    wallVector.push_back(cornerWall1);

    RectangleShape cornerWall2(Vector2f(5, 800));
    cornerWall2.setPosition(1, 1);
    wallVector.push_back(cornerWall2);

    RectangleShape cornerWall3(Vector2f(1080, 5));
    cornerWall3.setPosition(1, 795);
    wallVector.push_back(cornerWall3);

    RectangleShape cornerWall4(Vector2f(5, 800));
    cornerWall4.setPosition(1075, 1);
    wallVector.push_back(cornerWall4);
}

void checkCollisionWithCoins(int& score) 
{
    for (auto& coin : coins) 
    {
        if (!coin.taken && pacmanSprite.getGlobalBounds().intersects(coin.sprite.getGlobalBounds())) 
        {
            coin.taken = true;
            score += 10;
            cout<<"Score: "<<score<<endl;
        }
    }
}

void drawCoins(RenderWindow& window) 
{
    for (auto& coin : coins) 
        if (!coin.taken) 
            window.draw(coin.sprite);
}

void drawWalls(RenderWindow& window) 
{
    for (const auto& wall : wallVector) 
    {
        RectangleShape wallCopy = wall; // Make a copy of the wall object
        wallCopy.setFillColor(Color::Blue); // Set fill color on the copy
        window.draw(wallCopy); // Draw the copy
    }
}

void checkCoinDimensions() 
{
    if (!coins.empty()) 
    {
        // Access the first coin in the vector
        Coin& firstCoin = coins.front();

        // Get the local bounds of the sprite (without transformations)
        FloatRect localBounds = firstCoin.sprite.getLocalBounds();

        // Get the global bounds of the sprite (with transformations applied)
        FloatRect globalBounds = firstCoin.sprite.getGlobalBounds();

        // Output the dimensions
        cout << "Local Bounds: Width = " << localBounds.width << ", Height = " << localBounds.height << endl;
        cout << "Global Bounds: Width = " << globalBounds.width << ", Height = " << globalBounds.height << endl;
    } 
    else 
    {
        cout << "No coins available." << endl;
    }
}



void* game_thread(void *arg)
{
    // Create RenderWindow here
    RenderWindow window1(VideoMode(1080, 800), "Game");
    window1.setPosition(Vector2i(100, 100));
    window1.setFramerateLimit(60);

    initWalls();
    initCoins();

    //checkCoinDimensions();

    // Load pacman image
    Texture pacmanTexture;
    if (!pacmanTexture.loadFromFile("PacmanR.jpeg")) {
        cerr << "Failed to load pacman.jpg" << endl;
        pthread_exit(NULL);
    }
    pacmanSprite.setTexture(pacmanTexture);
    pacmanSprite.setScale(0.17, 0.17);

    // int i=1;
    // for (auto& coin : coins) 
    // {
    //     cout << i++ <<". Position: X = " << coin.sprite.getPosition().x << ", Y = " << coin.sprite.getPosition().x << endl;
    // }

    while (window1.isOpen())
    {
        Event event;
        while (window1.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window1.close();
                gamerunning = false;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) 
        {
            pthread_mutex_lock(&usermutex);
            userDirection = 'U';
            pthread_mutex_unlock(&usermutex);
            pacmanTexture.loadFromFile("PacmanU.jpeg");
        } 
        else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) 
        {
            pthread_mutex_lock(&usermutex);
            userDirection = 'L';
            pthread_mutex_unlock(&usermutex);
            pacmanTexture.loadFromFile("PacmanL.jpeg");

        } 
        else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) 
        {
            pthread_mutex_lock(&usermutex);
            userDirection = 'D';
            pthread_mutex_unlock(&usermutex);
            pacmanTexture.loadFromFile("PacmanD.jpeg");

        } 
        else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) 
        {
            pthread_mutex_lock(&usermutex);
            userDirection = 'R';
            pthread_mutex_unlock(&usermutex);
            pacmanTexture.loadFromFile("PacmanR.jpeg");

        }

        
        
        window1.clear();

        // Set position of pacman sprite to userCoordinates
        pthread_mutex_lock(&usermutex2);
        pacmanSprite.setPosition(userCoordinates.x, userCoordinates.y);
        pthread_mutex_unlock(&usermutex2);

        drawWalls(window1);
        drawCoins(window1);

        window1.draw(pacmanSprite);

        window1.display();

        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            window1.close();
            gamerunning = false;
        }

    }
    pthread_exit(NULL);
}
#endif