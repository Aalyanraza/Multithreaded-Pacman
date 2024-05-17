#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "menu.h"
#include "shared_variables.h"
using namespace std;


void* handleEnemyCollisionWithPellets(void* enemyIdPtr) 
{
    int enemyId = *((int*)enemyIdPtr); // Extract enemyId from the void pointer
    
    while (gamerunning) 
    {
        pthread_mutex_lock(&pelletmutex);

        if (powerPellet.available && enemys[enemyId].sprite.getGlobalBounds().intersects(powerPellet.sprite.getGlobalBounds())) 
        {
            powerPellet.available = false;
            enemys[enemyId].pelletEaten = true; // Change to boolean value
            
            counts = 0;
            cout << "Pellet eaten by " << enemyId << endl;
            pthread_mutex_lock(&pelletmutex);
        }
        if (powerPellet1.available && enemys[enemyId].sprite.getGlobalBounds().intersects(powerPellet1.sprite.getGlobalBounds())) 
        {
            powerPellet1.available = false;
            enemys[enemyId].pelletEaten = true; // Change to boolean value
            
            counts = 0;
            cout << "Pellet eaten by " << enemyId << endl;
            pthread_mutex_lock(&pelletmutex);
        }

        pthread_mutex_unlock(&pelletmutex);
    }
    return nullptr; // Return nullptr instead of void pointer
}
