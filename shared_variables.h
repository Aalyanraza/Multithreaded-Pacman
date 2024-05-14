#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H

#include <vector>
#include <pthread.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Define a struct to represent coordinates
struct Coordinates {
    int x;
    int y;
};

struct Coin {
    int x, y;
    Sprite sprite;
    bool taken;

    Coin(int i, int j, Sprite sprite1) : x(i), y(j), taken(false) 
    {
        sprite = sprite1;
        sprite.setPosition(x, y);
    }
};

struct Enemy
{
    int x, y;
    char direction;
    Sprite sprite;
    bool alive;

    Enemy(int i, int j, Sprite sprite1) : x(i), y(j), direction('L'), alive(true) 
    {
        sprite = sprite1;
        sprite.setPosition(x, y);
    }
};


// Declare shared variables for enemies, users, and walls
extern vector<pthread_mutex_t> enemymutexes;
extern vector<Coordinates> enemyCoordinates;
extern vector<RectangleShape> wallVector;
extern vector<Coin> coins;

extern pthread_mutex_t usermutex;
extern pthread_mutex_t usermutex2;

extern Coordinates userCoordinates;
extern char userDirection;
extern bool gamerunning;
extern int score;

extern Texture coinTexture;
extern Sprite pacmanSprite;


#endif 
