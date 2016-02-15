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
    this->trueX = x;
    this->trueY = y;
    this->w = 32;
    this->h = 32;
    this->gun = (new Gun(4, 10, 8)); // ROF, DMG, VEL
    this->angle = 0;
    this->speed = speed;
}

void Player::update()
{
    float prevX = trueX;
    float prevY = trueY;

    // Movement
    if (this->keysDown[0] == true) {
        trueY -= speed;
        for (auto &i : game.sprites) {
            i->setY(i->y+(this->speed));
        }
        for (auto &i : game.bullets) {
            i->y+=this->speed;
        }
    }
    if (this->keysDown[1] == true) {
        trueX -= speed;
        for (auto &i : game.sprites) {
            i->setX(i->x+(this->speed));
        }
        for (auto &i : game.bullets) {
            i->x+=this->speed;
        }
    }
    if (this->keysDown[2] == true) {
        trueY += speed;
        for (auto &i : game.sprites) {
            i->setY(i->y-(this->speed));
        }
        for (auto &i : game.bullets) {
            i->y-=this->speed;
        }
    }
    if (this->keysDown[3] == true) {
        trueX += speed;
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
                trueY += speed;
                for (auto &i : game.sprites) {
                    i->setY(i->y-(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->y-=this->speed;
                }
            };
            if ( this->keysDown[1] ) {
                trueX += speed;
                for (auto &i : game.sprites) {
                    i->setX(i->x-(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->x-=this->speed;
                }
            };
            if ( this->keysDown[2] ) {
                trueY -= speed;
                for (auto &i : game.sprites) {
                    i->setY(i->y+(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->y+=this->speed;
                }
            };
            if ( this->keysDown[3] ) {
                trueX -= speed;
                for (auto &i : game.sprites) {
                    i->setX(i->x+(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->x+=this->speed;
                }
            };
        }
    }

    currectSpeed[0] = (trueX - prevX);
    currectSpeed[1] = (trueY - prevY);

    // Shooting
    if (gun != nullptr)
    {
        // Update gun
        gun->update();
        // Set properties equal to player
        gun->x = getX()-16;
        gun->y = getY()-16;
        gun->angle = getAngle();
        gun->velX = currectSpeed[0];
        gun->velY = currectSpeed[1];

        // Shoot
        if (mouse == true && gun->cooldown <= 0)
        {
            gun->fire();
            // Reset the cooldown
            gun->cooldown = gun->fireRate;
        }
    }
}
