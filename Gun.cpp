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
    fireRate = 50 - (modifier + rand()%10);
    if (fireRate < 10)
        fireRate = 10;
    damage = rand()%3 + modifier;
    if (damage > 15)
        damage = 15;
    velocity = rand()%3 + modifier;
    if (velocity > 10)
        velocity = 10;
}
