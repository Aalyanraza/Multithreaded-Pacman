#ifndef MENU_H
#define MENU_H


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace std;


void* menu_thread(void *arg)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu");
    window.setPosition(sf::Vector2i(100, 100));

    window.setFramerateLimit(60);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString("Press Enter to start the game");
    text.setPosition(200, 200);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(text);
        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            window.close();
        }
    }
    pthread_exit(NULL);
}

#endif
