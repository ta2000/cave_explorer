#include "Gun.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>

extern Game game;

Gun::Gun(int fireRate, float damage, float velocity)
{
    this->fireRate = fireRate;
    this->cooldown = rand() % 50;
    this->damage = damage;
    this->velocity = velocity;
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
    game.bullets.push_back( new Bullet(x, y, angle, damage, velocity+(game.scale/2), velX, velY) );
    cooldown = fireRate;
}
