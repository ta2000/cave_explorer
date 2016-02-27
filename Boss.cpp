#include "Boss.h"
#include "Game.h"

#include "Wall.h"
#include "Enemy.h"
#include "Gun.h"
#include "GunItem.h"
#include "Health.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <algorithm>

#define PI 3.14159265359

extern Game game;

Boss::Boss(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->setW(128);
    this->setH(128);

    this->hp = game.levelNum*3;

    this->gun = new Gun(2, game.levelNum/5, -6, true);
    this->speed = game.player->speed-2;
}

void Boss::shoot(float velX, float velY, float direction)
{
    game.bullets.push_back( new Bullet(getX()-getW()/2, getY()-getH()/2, direction*PI/180, gun->damage, gun->velocity+12, velX, velY, true) );
    gun->cooldown = gun->fireRate;
}

void Boss::draw()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    Sprite::draw();
}

bool Boss::update()
{
    float prevX = getX();
    float prevY = getY();

    if (hp != game.levelNum*3 && !activated)
    {
        activated = true;
        phase = 0;
    }

    if (activated)
    {
        // Update phase counter
        --phaseCounter;
        if (phaseCounter <= 0)
        {
            phaseCounter = 200;
            ++phase;
        }
        if (phase > 2)
            phase = 0;
    }

    // Set exit's x/y to itself to prevent player from leaving boss fight
    game.levelExit->setX(getX()-getW()/2+game.levelExit->getW()/2);
    game.levelExit->setY(getY()-getH()/2+game.levelExit->getH()/2);

    // Determine actions based on phase
    switch(phase)
    {
    case 0: // Chasing player
         // Face towards player
        setAngle(atan2(getY() - game.player->getY(), getX() - game.player->getX()));
        setX(getX() + cos( getAngle()+PI )*this->speed);
        setY(getY() + sin( getAngle()+PI )*this->speed);
        break;
    case 1: // Firing in circle
       // Create space for firing
        for (auto i = game.sprites.begin(); i != game.sprites.end();)
        {
            if ( distance(*i)<=300 && (*i)!=this && (dynamic_cast<Wall*>(*i)!=NULL) )
            {
                // Destroy walls if colliding
                delete (*i);
                game.sprites.erase(i++);
            }
            ++i;
        }
        shootingDirection+=11;
        if (shootingDirection >= 360)
            shootingDirection -= 360;

        if (gun != nullptr)
        {
            // Update gun
            gun->update();
            // Shoot as soon as possible
            if (gun->cooldown <= 0)
            {
                shoot(getX() - prevX, getY() - prevY, shootingDirection);
            }
        }
        break;
    case 2:
        setAngle(atan2(getY() - game.player->getY(), getX() - game.player->getX()));
        if (rand() % 40 == 0)
        {
            game.sprites.push_front(new Enemy(getX(), getY()));
        }
        break;
    }

    // Damage player if too close and move player away
    if (collision(game.player))
    {
        --game.player->hp;
        if ( game.player->getY() > getY() ) {
            for (auto &i : game.sprites) {
                i->setY(i->y-(this->speed*2));
            }
            for (auto &i : game.bullets) {
                i->y-=this->speed*2;
            }
        };
        if ( game.player->getX() > getX() ) {
            for (auto &i : game.sprites) {
                i->setX(i->x-(this->speed*2));
            }
            for (auto &i : game.bullets) {
                i->x-=this->speed*2;
            }
        };
        if ( game.player->getY() < getY() ) {
            for (auto &i : game.sprites) {
                i->setY(i->y+(this->speed*2));
            }
            for (auto &i : game.bullets) {
                i->y+=this->speed*2;
            }
        };
        if ( game.player->getX() < getX() ) {
            for (auto &i : game.sprites) {
                i->setX(i->x+(this->speed*2));
            }
            for (auto &i : game.bullets) {
                i->x+=this->speed*2;
            }
        };
    }

    // Check collisions
    for (auto i = game.sprites.begin(); i != game.sprites.end();)
    {
        if ( distance(*i)<=256 && (*i)!=this && (dynamic_cast<Wall*>(*i)!=NULL) )
        {
            if ( collision(*i) )
            {
                // Destroy walls if colliding
                delete (*i);
                game.sprites.erase(i++);
            }
        }
        ++i;
    }

    // Delete if not alive
    bool alive = true;
    for (auto i = game.bullets.begin(); i != game.bullets.end();)
    {
        if (bulletCollision(*i) && (*i)->isEnemy==false)
        {
            hp -= (*i)->damage;
            if (hp <= 0)
            {
                // Flag for deletion
                alive = false;
                // Drop health packs as reward
                for (int i=0; i<5; i++)
                {
                    game.sprites.push_back(new Health(getX() - getW() + rand() % (int)getW(), getY() - getH() + rand() % (int)getH()));
                }
            }
            // Delete colliding bullet
            delete (*i);
            game.bullets.erase(i++);
        }
        ++i;
    }
    return alive;
}


