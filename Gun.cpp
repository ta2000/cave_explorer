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

    this->fireRate = fireRate;
    this->damage = damage;
    this->spread = spread;
}

void Gun::fire(float damage, float spread)
{

}
