#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "menu.h"
#include "game.h"
#include "shared_variables.h"
#include "collision.h"
using namespace std;

pthread_mutex_t keyMutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t permitMutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t keyMutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t permitMutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t diners = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t diners1 = PTHREAD_MUTEX_INITIALIZER;

void ghostBehavior(int ghostID) {

    if (ghostID == 0)
    {
        pthread_mutex_lock(&keyMutex1);
        pthread_mutex_lock(&diners);
        pthread_mutex_lock(&permitMutex1);

         cout << "Ghost " << ghostID << " left the ghost house." << endl;

        sleep(2);
        pthread_mutex_unlock(&diners);
        pthread_mutex_unlock(&keyMutex1);
        pthread_mutex_unlock(&permitMutex1);
        enemys[ghostID].x = 385;
        enemys[ghostID].y= 355;
        


    }
    else if (ghostID == 1)
    {
        pthread_mutex_lock(&keyMutex2);
        pthread_mutex_lock(&diners1);
        pthread_mutex_lock(&permitMutex1);
       
        cout << "Ghost " << ghostID << " left the ghost house." << endl;

        sleep(2);
        pthread_mutex_unlock(&diners1);
        pthread_mutex_unlock(&keyMutex2);
        
        pthread_mutex_unlock(&permitMutex1);
        enemys[ghostID].x= 385;
        enemys[ghostID].y = 455;
        

    }
    else if (ghostID == 2)
    {   
        pthread_mutex_lock(&keyMutex2);
        pthread_mutex_lock(&diners);
        pthread_mutex_lock(&permitMutex2);

         cout << "Ghost " << ghostID << " left the ghost house." << endl;
        sleep(2);
        pthread_mutex_unlock(&diners);

        pthread_mutex_unlock(&keyMutex2);
        pthread_mutex_unlock(&permitMutex2);
        enemys[ghostID].x= 655;
        enemys[ghostID].y = 455;

    }
    else if (ghostID == 3)
    {

        pthread_mutex_lock(&keyMutex1);
        pthread_mutex_lock(&diners1);
        pthread_mutex_lock(&permitMutex2);

         cout << "Ghost " << ghostID << " left the ghost house." << endl;
        sleep(2);
        pthread_mutex_unlock(&diners1);

        pthread_mutex_unlock(&keyMutex1);
        pthread_mutex_unlock(&permitMutex2);
        enemys[ghostID].x = 655;
        enemys[ghostID].y= 455;

    }    
   
}


void* enemyThread(void* num)
{
    Texture texture;
    Sprite sprite;
    Enemy enemy;
    int cou=0;

    pthread_mutex_lock(&enemymutex1);
    int enemyId=enemys.size();
    if (enemyId == 0)
    {
        texture.loadFromFile("ghost1.jpeg");
        sprite.setTexture(texture);
        enemy.x = 455;
        enemy.y = 355;
        enemy.sprite = sprite;
    }
    else if (enemyId == 1)
    {
        texture.loadFromFile("ghost2.jpeg");
        sprite.setTexture(texture);
        enemy.x = 455;
        enemy.y = 455;
        enemy.sprite = sprite;  
    }
    else if (enemyId == 2)
    {   
        texture.loadFromFile("ghost3.jpeg");
        sprite.setTexture(texture);
        enemy.x = 585;
        enemy.y = 355;
        enemy.sprite = sprite;
    }
    else if (enemyId == 3)
    {
        texture.loadFromFile("ghost4.jpeg");
        sprite.setTexture(texture);
        enemy.x = 585;
        enemy.y = 455;
        enemy.sprite = sprite;
    }    
    
    enemy.sprite.setPosition(enemy.x, enemy.y);
    enemy.sprite.setScale(0.2,0.2);

    enemys.push_back(enemy);
    enemymutexes.push_back(PTHREAD_MUTEX_INITIALIZER);
    pthread_mutex_unlock(&enemymutex1);

    pthread_mutex_lock(&pelletmutex);

    Texture pillTexture;
    !pillTexture.loadFromFile("pill.jpeg"); 
    powerPellet.sprite.setTexture(pillTexture);
    powerPellet.sprite.setPosition(100, 500);
    powerPellet.sprite.setScale(0.2, 0.2);
    powerPellet.available = true;


    powerPellet1.sprite.setTexture(pillTexture);
    powerPellet1.sprite.setPosition(100, 400);
    powerPellet1.sprite.setScale(0.2, 0.2);
    powerPellet1.available = true;

    // Unlock the mutex
    pthread_mutex_unlock(&pelletmutex);

    pthread_t coll;
    pthread_create(&coll, NULL, handleEnemyCollisionWithPellets, (void*)(&enemyId));

    while (gamerunning)
    {
        if(cou==0)
        {
            ghostBehavior(enemyId);
            cou++;
            enemy.sprite.setPosition(enemys[enemyId].x, enemys[enemyId].y);
        }

        pthread_mutex_lock(&enemymutexes[enemyId]);
        if (enemys[enemyId].sprite.getGlobalBounds().intersects(pacmanSprite.getGlobalBounds()))
        {
            if (pwerTaken)
            {
                cout << "Ghost " << enemyId << " was eaten." << endl;
                enemys[enemyId].x = 455;
                enemys[enemyId].y = 355;
                pthread_mutex_unlock(&enemymutexes[enemyId]);
                ghostBehavior(enemyId);
                pthread_mutex_lock(&enemymutexes[enemyId]);
            }
            else
            {
                lives--;
                cout << "Lives: " << lives << endl;
                pthread_mutex_lock(&usermutex2);
                if (userCoordinates.x > 500)
                    userCoordinates = {6, 760};
                else
                    userCoordinates = {1030, 6};
                pthread_mutex_unlock(&usermutex2);
            }
        }
        else if (enemys[enemyId].x < userCoordinates.x && !isCollisionWithWall(enemys[enemyId].x + 1, enemys[enemyId].y, enemys[enemyId].sprite))
            enemys[enemyId].x += 1;
        else if (enemys[enemyId].x > userCoordinates.x && !isCollisionWithWall(enemys[enemyId].x - 1, enemys[enemyId].y, enemys[enemyId].sprite))
            enemys[enemyId].x -= 1;
        else if (enemys[enemyId].y < userCoordinates.y && !isCollisionWithWall(enemys[enemyId].x, enemys[enemyId].y + 1, enemys[enemyId].sprite))
            enemys[enemyId].y += 1;
        else if (enemys[enemyId].y > userCoordinates.y && !isCollisionWithWall(enemys[enemyId].x, enemys[enemyId].y - 1, enemys[enemyId].sprite))
            enemys[enemyId].y -= 1;
        
        pthread_mutex_unlock(&enemymutexes[enemyId]);

        if (enemys[enemyId].pelletEaten && counts == 625)
        {
            cout << "Pellet eaten done" << endl;
            enemys[enemyId].pelletEaten = false;
            powerPellet.available = true;
            powerPellet1.available = true;
            pthread_mutex_unlock(&pelletmutex);
        }
        else if (enemys[enemyId].pelletEaten)
        {
            counts++;
            sleep(milliseconds(5));
        }
        else
            sleep(milliseconds(8));
        
    }
    void* status;
    return status;
}
