//
// Created by hodgk on 09/04/2020.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Obstacle.h"
float Obstacle::speed = 250.f;
Obstacle::Obstacle(float x, float floorY) {
    this->width = 30;
    this->height = 55;
    this->y = floorY - height;
    this->x = x;
    this->x += (rand() % 150 -75);
    rect.setSize(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color(240, 50, 50, 255));

}

void Obstacle::move(double delta) {
    this->x -= Obstacle::speed * delta;
}

void Obstacle::draw(sf::RenderWindow *window) {
    rect.setPosition(x, y);
    window->draw(rect);
}