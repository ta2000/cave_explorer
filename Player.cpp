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
    this->gun = (new Gun(10, 10, 8, false)); // ROF, DMG, VEL
    this->angle = 0;
    this->speed = speed;
}

void Player::shoot(float velX, float velY)
{
    game.bullets.push_back( new Bullet(getX()-game.scale/2, getY()-game.scale/2, getAngle(), gun->damage, gun->velocity+12, velX, velY, false) );
    gun->cooldown = gun->fireRate;
}

bool Player::update()
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

    // Shooting
    if (gun != nullptr)
    {
        // Update gun
        gun->update();
        // Shoot
        if (mouse == true && gun->cooldown <= 0)
        {
            shoot((trueX - prevX), (trueY - prevY));
        }
    }

    return true;
}
