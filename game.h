#ifndef GAME_H
#define GAME_H


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace std;
using namespace sf;


void* game_thread(void *arg)
{
    RenderWindow window(VideoMode(800, 600), "Game");
    window.setPosition(sf::Vector2i(100, 100));
    window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("arial.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setString("Press Enter to start the game");
    text.setPosition(200, 200);
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
        window.draw(text);
        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            window.close();
        }
    }
    pthread_exit(NULL);
}

#endif