#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "menu.h"
using namespace std;

int main() 
{
    pthread_t menu;
    pthread_create(&menu, NULL, menu_thread, NULL);
    pthread_join(menu, NULL);
    return 0;
}
