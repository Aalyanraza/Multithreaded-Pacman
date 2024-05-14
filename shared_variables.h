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
    Sprite sprite;
    bool alive;

    Enemy() : x(0), y(0), alive(true) 
    {
        Texture texture;
        texture.loadFromFile("ghost1.jpeg");
        sprite.setTexture(texture);
        sprite.setPosition(x, y);

    }

    Enemy(int i, int j, Sprite sprite1) : x(i), y(j), alive(true) 
    {
        sprite = sprite1;
        sprite.setPosition(x, y);
    }
};


// Declare shared variables for enemies, users, and walls
extern vector<pthread_mutex_t> enemymutexes;
extern vector<Enemy> enemys;
extern vector<RectangleShape> wallVector;
extern vector<Coin> coins;

extern pthread_mutex_t usermutex;
extern pthread_mutex_t usermutex2;
extern pthread_mutex_t enemymutex1;


extern Coordinates userCoordinates;
extern char userDirection;
extern bool gamerunning;
extern int score;
extern int lives;

extern Texture coinTexture;
extern Sprite pacmanSprite;

// shared function

bool isCollisionWithWall(int x, int y, const Sprite& sprite);

#endif 
