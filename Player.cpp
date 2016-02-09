#include "Player.h"
#include "Game.h"

#include <GL/glut.h>

Player::Player(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
}

