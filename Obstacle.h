//
// Created by hodgk on 09/04/2020.
//

#ifndef RUN_OBSTACLE_H
#define RUN_OBSTACLE_H


#include <SFML/Graphics/RectangleShape.hpp>

class Obstacle {

public:
    Obstacle(float x =0, float floorY = 0);
    float x;
    float y;
    float height;
    float width;
    void draw(sf::RenderWindow* window);
    void move(double);
    sf::RectangleShape rect;
    static float speed;

};


#endif //RUN_OBSTACLE_H
