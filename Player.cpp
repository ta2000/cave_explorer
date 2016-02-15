#include "Player.h"
#include "Game.h"
#include "Wall.h"
#include "Gun.h"

#include <GL/glut.h>
#include <iostream>

Game game;

Player::Player(float x, float y, float speed) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
    this->gun = (new Gun(20, 10, 16)); // ROF, DMG, VEL
    this->angle = 0;
    this->speed = speed;
}

void Player::update()
{
    // Shooting
    if (gun != nullptr)
    {
        // Update gun
        gun->update();
        // Set properties equal to player
        gun->x = getX();
        gun->y = getY();
        gun->angle = getAngle();

        // Shoot
        if (mouse == true && gun->cooldown <= 0)
        {
            gun->fire();
            // Reset the cooldown
            gun->cooldown = gun->fireRate;
        }
    }

    // Movement
    if (this->keysDown[0] == true) {
        for (auto &i : game.sprites) {
            i->setY(i->y+(this->speed));
        }
        for (auto &i : game.bullets) {
            i->y+=this->speed;
        }
    }
    if (this->keysDown[1] == true) {
        for (auto &i : game.sprites) {
            i->setX(i->x+(this->speed));
        }
        for (auto &i : game.bullets) {
            i->x+=this->speed;
        }
    }
    if (this->keysDown[2] == true) {
        for (auto &i : game.sprites) {
            i->setY(i->y-(this->speed));
        }
        for (auto &i : game.bullets) {
            i->y-=this->speed;
        }
    }
    if (this->keysDown[3] == true) {
        for (auto &i : game.sprites) {
            i->setX(i->x-(this->speed));
        }
        for (auto &i : game.bullets) {
            i->x-=this->speed;
        }
    }

    // Check collisions
    for (auto &i : game.sprites) {
        if (collision(i) && dynamic_cast<Wall*>(i) != NULL) // Only collide if wall
        {
            if ( this->keysDown[0] ) {
                for (auto &i : game.sprites) {
                    i->setY(i->y-(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->y-=this->speed;
                }
            };
            if ( this->keysDown[1] ) {
                for (auto &i : game.sprites) {
                    i->setX(i->x-(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->x-=this->speed;
                }
            };
            if ( this->keysDown[2] ) {
                for (auto &i : game.sprites) {
                    i->setY(i->y+(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->y+=this->speed;
                }
            };
            if ( this->keysDown[3] ) {
                for (auto &i : game.sprites) {
                    i->setX(i->x+(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->x+=this->speed;
                }
            };
        }
    }
}
