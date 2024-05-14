#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "menu.h"
#include "game.h"
using namespace std;


void* enemyThread(void* num)
{
    Texture texture;
    Sprite sprite;
    Enemy enemy;

    pthread_mutex_lock(&enemymutex1);
    int enemyId=enemys.size();
    if (enemyId == 0)
    {
        texture.loadFromFile("ghost1.jpeg");
        sprite.setTexture(texture);
        enemy.x = 385;
        enemy.y = 355;
        enemy.sprite = sprite;
    }
    else if (enemyId == 1)
    {
        texture.loadFromFile("ghost2.jpeg");
        sprite.setTexture(texture);
        enemy.x = 385;
        enemy.y = 455;
        enemy.sprite = sprite;  
    }
    else if (enemyId == 2)
    {   
        texture.loadFromFile("ghost3.jpeg");
        sprite.setTexture(texture);
        enemy.x = 655;
        enemy.y = 355;
        enemy.sprite = sprite;
    }
    else if (enemyId == 3)
    {
        texture.loadFromFile("ghost4.jpeg");
        sprite.setTexture(texture);
        enemy.x = 655;
        enemy.y = 455;
        enemy.sprite = sprite;
    }    
    enemy.sprite.setPosition(enemy.x, enemy.y);
    enemy.sprite.setScale(0.2,0.2);

    enemys.push_back(enemy);
    enemymutexes.push_back(PTHREAD_MUTEX_INITIALIZER);
    pthread_mutex_unlock(&enemymutex1);


    while (gamerunning)
    {
        pthread_mutex_lock(&enemymutexes[enemyId]);
        if (enemys[enemyId].x < userCoordinates.x && !isCollisionWithWall(enemys[enemyId].x + 1, enemys[enemyId].y, enemys[enemyId].sprite))
            enemys[enemyId].x += 1;
        else if (enemys[enemyId].x > userCoordinates.x && !isCollisionWithWall(enemys[enemyId].x - 1, enemys[enemyId].y, enemys[enemyId].sprite))
                enemys[enemyId].x -= 1;
        else if (enemys[enemyId].y < userCoordinates.y && !isCollisionWithWall(enemys[enemyId].x, enemys[enemyId].y + 1, enemys[enemyId].sprite))
                enemys[enemyId].y += 1;
        else if (enemys[enemyId].y > userCoordinates.y && !isCollisionWithWall(enemys[enemyId].x, enemys[enemyId].y - 1, enemys[enemyId].sprite))
                enemys[enemyId].y -= 1;
        else if (enemys[enemyId].x == userCoordinates.x && enemys[enemyId].y == userCoordinates.y)
        {
            lives--;
            cout<<"Lives: "<<lives<<endl;
            userCoordinates={6,760};
        }
        pthread_mutex_unlock(&enemymutexes[enemyId]);
        sleep(milliseconds(8));

    }
}