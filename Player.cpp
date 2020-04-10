//
// Created by hodgk on 08/04/2020.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Player.h"

Player::Player(double y, double width) {
    this->x = 50;
    this->y = y;
    this->width = width;
    this->gravity = 1500;
    this->yVel = 0;
    this->jumpSpeed = -550;

    rectangleShape.setSize(sf::Vector2f(width, width));
    rectangleShape.setPosition(this->x, this->y);
    rectangleShape.setFillColor(sf::Color::Black);
}

void Player::levelUp() {
    this->gravity += 7;
    this->jumpSpeed-= 2;
}

bool Player::collides(sf::RectangleShape *rect) {
    return this->x < rect->getPosition().x + rect->getSize().x && this->x + this->width > rect->getPosition().x &&
           this->y < rect->getPosition().y + rect->getSize().y && this->y + this->width > rect->getPosition().y;
}

void Player::updateMovement(double delta) {
    yVel += gravity * delta;

    y += yVel * delta;
}

void Player::onFloor(sf::RectangleShape floor) {
    this->yVel = 0;
    this->jumpAvailable = true;
    this->y = floor.getPosition().y - this->width;
}

void Player::draw(sf::RenderWindow *window) {
    rectangleShape.setPosition(x, y);
    //window->setActive(true);
    window->draw(rectangleShape);
}

void Player::jump() {
    if (!jumpAvailable) return;
    this->yVel = jumpSpeed;
    jumpAvailable = false;
}
