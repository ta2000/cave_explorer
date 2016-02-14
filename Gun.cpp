#include "Gun.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

Gun::Gun(float x, float y, int fireRate, int damage, int spread) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 16;
    this->h = 32;

    this->fireRate = fireRate;
    this->cooldown = 0;
    this->damage = damage;
    this->spread = spread;
}

void Gun::update()
{
    if (cooldown > 0)
    {
        cooldown--;
    }
}

void Gun::fire()
{
    std::cout << "Bang!" << std::endl;
}
