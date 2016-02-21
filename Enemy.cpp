#include "Enemy.h"
#include "Game.h"

#include "Wall.h"
#include "Gun.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <algorithm>

#define PI 3.14159265359

extern Game game;

Enemy::Enemy(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;

    this->gun = new Gun(40, 2, 1, true);
    this->speed = rand() % 2 + 2;
}

void Enemy::shoot(float velX, float velY)
{
    game.bullets.push_back( new Bullet(getX()-game.scale/2, getY()-game.scale/2, getAngle()+PI, gun->damage, gun->velocity+12, velX, velY, true) );
    gun->cooldown = gun->fireRate;
}

bool Enemy::update()
{
    float prevX = getX();
    float prevY = getY();

    bool directions[4] = {false, false, false, false};
    bool wandering = false;

    // ================
    // ATTACKING PLAYER
    // ================
    if ( distance(game.player) < 400 )
    {
        targetX = game.player->x;
        targetY = game.player->y;
        // Decrement counter each frame
        attackMovementCounter--;
        // Prevent counter from being below 0
        if (attackMovementCounter < 0)
            attackMovementCounter = 0;
        // Randomize directions if counter = 0
        if (attackMovementCounter == 0)
        {
            shuffle(std::begin(mixedDirections), std::end(mixedDirections), std::default_random_engine(rand()));
            attackMovementCounter = rand() % 30 + 10;
        }

        if ( distance(game.player) > 200)
        {
           if ( getX() < targetX )
            directions[0] = true;
            else if ( getX() > targetX )
                directions[1] = true;
            if ( getY() < targetY )
                directions[2] = true;
            else if ( getY() > targetY )
                directions[3] = true;
        }
        else
        {
            // Move around player randomly
            if ( getX() < targetX )
                directions[mixedDirections[0]] = true;
            else if ( getX() > targetX )
                directions[mixedDirections[1]] = true;
            if ( getY() < targetY )
                directions[mixedDirections[2]] = true;
            else if ( getY() > targetY )
                directions[mixedDirections[3]] = true;
        }

        // Face towards target
        setAngle(atan2(getY() - targetY, getX() - targetX));

        // Fire gun if armed
        if (gun != nullptr)
        {
            // Update gun
            gun->update();
            // Shoot as soon as possible
            if (gun->cooldown <= 0)
            {
                shoot(getX() - prevX, getY() - prevY);
            }
        }
    }
    // =========
    // WANDERING
    // =========
    else
    {
        wandering = true;

        directions[wanderingDirection] = true;
    }

    // Check collisions
    for (auto &i : game.sprites) {
        if ( distance(i)<=128 && i!=this && (dynamic_cast<Wall*>(i)!=NULL) )
        {
            for (int rayAngle=0; rayAngle<360; rayAngle+=90)
            {

                if ( pointWithinSprite(
                    getX()+(game.scale/2) - cos(rayAngle*PI/180)*game.scale,
                    getY()+(game.scale/2) - sin(rayAngle*PI/180)*game.scale,
                    i ) || collision(i) )
                {
                    if (rayAngle == 180)
                        directions[0] = false;
                    else if (rayAngle == 0)
                        directions[1] = false;
                    if (rayAngle == 270)
                        directions[2] = false;
                    else if (rayAngle == 90)
                        directions[3] = false;
                    if (wandering)
                        wanderingDirection = rand() % 4;
                }

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


    // Delete if not alive
    bool alive = true;
    for (auto i = game.bullets.begin(); i != game.bullets.end();)
    {
        if (bulletCollision(*i) && (*i)->isEnemy==false)
        {
            alive = false;
            delete (*i);
            game.bullets.erase(i++);
        }
        ++i;
    }
    return alive;
}

