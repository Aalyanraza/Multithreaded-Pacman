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

int main() 
{
    pthread_t menu, game;
    pthread_create(&menu, NULL, menu_thread, NULL);
    pthread_join(menu, NULL);
    pthread_create(&game, NULL, game_thread, NULL);
    pthread_join(game, NULL);
    return 0;
}
