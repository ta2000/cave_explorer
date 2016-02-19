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

    bool directions[4] = {false, false, false, false};

    // ================
    // ATTACKING PLAYER
    // ================
    if ( distance(game.player) < 300)
    {
        setAngle(atan2(getY() - targetY, getX() - targetX));

        // Move
        if ( getX() < game.player->x )
            directions[0] = true;
        else if ( getX() > game.player->x )
            directions[1] = true;
        if ( getY() < game.player->y )
            directions[2] = true;
        else if ( getY() > game.player->y )
            directions[3] = true;


        // Check collisions
        for (auto &i : game.sprites) {
            if ( distance(i)<=128 && i!=this )
            {
                for (int rayAngle=0; rayAngle<360; rayAngle+=90)
                {
                    if ( pointWithinSprite(
                            getX()+16 - cos(rayAngle*PI/180)*64,
                            getY()+16 - sin(rayAngle*PI/180)*64,
                            i ) )
                    {
                        if (rayAngle == 180)
                            directions[0] = false;
                        else if (rayAngle == 0)
                            directions[1] = false;
                        if (rayAngle == 270)
                            directions[2] = false;
                        else if (rayAngle == 90)
                            directions[3] = false;
                    }
                }
            }
        }

        if (gun != nullptr)
        {
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

    // Move in current directions
    if ( directions[0] )
        setX( getX() + speed );
    else if ( directions[1] )
        setX( getX() - speed );
    if ( directions[2] )
        setY( getY() + speed );
    else if ( directions[3] )
        setY( getY() - speed );

}

