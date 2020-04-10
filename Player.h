//
// Created by hodgk on 08/04/2020.
//

#ifndef RUN_PLAYER_H
#define RUN_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(double y = 0, double width = 30);

    int width;
    double x;
    double y;

    void jump();

    void draw(sf::RenderWindow *window);

    void updateMovement(double delta);

    void onFloor(sf::RectangleShape floor);

    bool collides(sf::RectangleShape *rect);

    void levelUp();

private:
    sf::RectangleShape rectangleShape;
    double jumpSpeed;
    double gravity;
    double yVel;
    bool jumpAvailable;
};


#endif //RUN_PLAYER_H
