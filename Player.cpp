#include "Player.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

Player::Player(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
}

void Player::move()
{
    if (this->keysDown[0] == true) {
        this->setY(this->y-=3.0f);
    }
    if (this->keysDown[1] == true) {
        this->setX(this->x-=3.0f);
    }
    if (this->keysDown[2] == true) {
        this->setY(this->y+=3.0f);
    }
    if (this->keysDown[3] == true) {
        this->setX(this->x+=3.0f);
    }
}
