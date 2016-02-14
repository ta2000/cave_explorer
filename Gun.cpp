#include "Gun.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

Gun::Gun(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 16;
    this->h = 32;

    this->damage = damage;
    this->fireRate = fireRate;
    this->spread = spread;
}

