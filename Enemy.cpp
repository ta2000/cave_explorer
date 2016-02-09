#include "Enemy.h"
#include "Game.h"

#include <GL/glut.h>

Enemy::Enemy(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
}


