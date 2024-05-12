#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H

#include <vector>
#include <pthread.h>
using namespace std;

// Define a struct to represent coordinates
struct Coordinates {
    int x;
    int y;
};

struct wallcoordinates {
    int x;
    int y;
    int width;
    int height;
};

// Declare shared variables for enemies, users, and walls
extern vector<pthread_mutex_t> enemymutexes;
extern vector<Coordinates> enemyCoordinates;
extern pthread_mutex_t usermutex;
extern Coordinates userCoordinates;
extern vector<wallcoordinates> wallVector;

extern vector<char> enemyDirections;
extern char userDirection;

extern bool gamerunning;

#endif 
