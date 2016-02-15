#include "Enemy.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265359

extern Game game;

Enemy::Enemy(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;

    this->angle = 0.0;
    this->speed = (rand() % 3 + 2);
}

void Enemy::update()
{
    if ( distance(game.player) < 256)
    {
        setAngle(atan2(getY() - game.player->y, getX() - game.player->x));
        setX( getX() - cos( getAngle() )*speed );
        setY( getY() - sin( getAngle() )*speed );
    }
}
