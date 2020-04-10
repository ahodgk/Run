//
// Created by hodgk on 08/04/2020.
//

#ifndef RUN_GAME_H
#define RUN_GAME_H

#include "Player.h"
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <Windows.h>
//#include <ctime>
//#include <ratio>
#include <chrono>


class Game {

public:
    Game();
    int score= 0;

private:
    Player player;
    void launchGameLoop();
    void doLogic();
    sf::RenderWindow window;
    std::thread logicThread;
    std::thread renderThread;
    sf::RectangleShape floor;
    bool started = false;
    double obstacleDistance;
    Obstacle obstacles[20];
    sf::Text scoreText;
    sf::Font font;
    sf::Text menuText;
    void lose();
    void reset();
};


#endif //RUN_GAME_H
