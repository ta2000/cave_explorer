#include "Enemy.h"
#include "Game.h"

#include "Wall.h"
#include "Gun.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265359

extern Game game;

Enemy::Enemy(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;

    this->gun = new Gun(20, 2, 1);

    this->targetX = game.player->x;
    this->targetY = game.player->y;
    this->angle = 0.0;
    this->speed = 2;
}

void Enemy::update()
{
    float prevX = getX();
    float prevY = getY();

    if ( distance(game.player) < 300)
    {
        setAngle(atan2(getY() - targetY, getX() - targetX));

        // Move
        if ( getX() < game.player->x )
            setX( getX() + speed );
        else if ( getX() > game.player->x )
            setX( getX() - speed );
        if ( getY() < game.player->y )
            setY( getY() + speed );
        else if ( getY() > game.player->y )
            setY( getY() - speed );


        // Check collisions
        for (auto &i : game.sprites) {
            if ( collision(i) && (i->x != x && i->y != y) ) // Only collide if wall
            {
                if ( getX() < i->x ) // Right
                {
                    setX( getX() - speed*2 );
                }
                else if ( getX() > i->x ) // Left
                {
                    setX( getX() + speed*2 );
                }
                if ( getY() < i->y ) // Bottom
                {
                    setY( getY() - speed*2 );
                }
                else if ( getY() > i->y ) // Top
                {
                    setY( getY() + speed*2 );
                }
            }
        }

        // Update gun
        gun->update();
        // Set properties equal to this
        gun->x = getX()-16;
        gun->y = getY()-16;
        gun->angle = getAngle() + PI;
        gun->velX = getX() - prevX;
        gun->velY = getY() - prevY;
        // Shoot as soon as possible
        if (gun->cooldown <= 0)
        {
            gun->fire();
        }
    }


}
