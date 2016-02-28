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

void Gun::setRandomStats(int modifier)
{
    fireRate = 50 - (rand()%15 + modifier);
    if (fireRate < 6)
        fireRate = 6;
    damage = rand()%3 + modifier/4;
    if (damage > 10)
        damage = 10;
    velocity = rand()%5 + modifier;
    if (velocity > 12)
        velocity = 12;
}
