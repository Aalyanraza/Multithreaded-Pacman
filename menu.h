#ifndef MENU_H
#define MENU_H


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "game.h"
using namespace std;
using namespace sf;

void game()
{
    pthread_t game;
    pthread_create(&game, NULL, game_thread, NULL);
    pthread_join(game, NULL);
}

void instructions(RenderWindow& window)
{
    Font font;
    font.loadFromFile("arial.ttf");

    Text instructionsText;
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(24);
    instructionsText.setFillColor(Color::White);
    instructionsText.setString("Instructions:\n\n1. Use the arrow keys to move.\n2. Avoid ghosts.\n3. Eat pellets to score points.\n4. Eat power pellets to temporarily turn ghosts blue and eat them.\n\nPress any key to return to the menu.");

    window.clear();
    window.draw(instructionsText);
    window.display();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed)
                return;
    }
}

void highscores(RenderWindow& window)
{
    Font font;
    font.loadFromFile("arial.ttf");

    Text highscoresText;
    highscoresText.setFont(font);
    highscoresText.setCharacterSize(24);
    highscoresText.setFillColor(Color::White);
    highscoresText.setString("Highscores:\n\n1. Player1 - 1000\n2. Player2 - 800\n3. Player3 - 600\n\nPress any key to return to the menu.");

    window.clear();
    window.draw(highscoresText);
    window.display();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed)
                return;
    }
}

void* menu_thread(void *arg)
{
    RenderWindow window(VideoMode(1080, 800), "Menu");
    window.setPosition(Vector2i(100, 100));
    window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("arial.ttf");

    // Load the background image
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("menu background.jpg")) {
        cerr << "Failed to load background image!" << endl;
        return NULL;
    }
    Sprite backgroundSprite(backgroundTexture);

    Text menuOptions[4];
    string options[4] = {"Start Game", "Instructions", "Highscores", "Exit"};

    for (int i = 0; i < 4; ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setString(options[i]);
        menuOptions[i].setCharacterSize(24);
        menuOptions[i].setFillColor(Color::White);
        menuOptions[i].setPosition(50 + i * 300, 600);
    }

    int selectedOption = -1;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    for (int i = 0; i < 4; ++i)
                    {
                        if (menuOptions[i].getGlobalBounds().contains(mousePos))
                        {
                            selectedOption = i;
                            break;
                        }
                    }
                }
            }
        }

        window.clear();

        // Draw the background image
        window.draw(backgroundSprite);

        for (int i = 0; i < 4; ++i) {
            if (i == selectedOption) {
                menuOptions[i].setFillColor(Color::Green);
            } else {
                menuOptions[i].setFillColor(Color::White);
            }
            window.draw(menuOptions[i]);
        }
        window.display();

        if (selectedOption != -1)
        {
            switch (selectedOption)
            {
                case 0:
                    std::cout << "Starting game..." << std::endl;
                    // Add code to start the game
                    break;
                case 1:
                    std::cout << "Showing instructions..." << std::endl;
                    instructions(window);
                    break;
                case 2:
                    std::cout << "Showing highscores..." << std::endl;
                    highscores(window);
                    break;
                case 3:
                    window.close();
                    break;
            }
            selectedOption = -1; // Reset selected option
        }
    }

    pthread_exit(NULL);
}
#endif
