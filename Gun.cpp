#include "Gun.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>

extern Game game;

Gun::Gun(int fireRate, float damage, float velocity, bool isEnemy)
{
    this->fireRate = fireRate;
    this->cooldown = rand() % fireRate;
    this->damage = damage;
    this->velocity = velocity;
    this->isEnemy = isEnemy;
}

void Gun::update()
{
    if (cooldown > 0)
    {
        cooldown--;
    }
}
