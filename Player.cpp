#include "Player.h"
#include "Game.h"
#include "Wall.h"

#include <GL/glut.h>
#include <iostream>

Game game;

Player::Player(float x, float y, float speed) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
    this->angle = 0;
    this->speed = speed;
}

void Player::update()
{
    // Shooting

    // Movement
    if (this->keysDown[0] == true) {
        for (auto &i : game.sprites) {
            i->setY(i->y+(this->speed));
        }
    }
    if (this->keysDown[1] == true) {
        for (auto &i : game.sprites) {
            i->setX(i->x+(this->speed));
        }
    }
    if (this->keysDown[2] == true) {
        for (auto &i : game.sprites) {
            i->setY(i->y-(this->speed));
        }
    }
    if (this->keysDown[3] == true) {
        for (auto &i : game.sprites) {
            i->setX(i->x-(this->speed));
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
            };
            if ( this->keysDown[1] ) {
                for (auto &i : game.sprites) {
                    i->setX(i->x-(this->speed));
                }
            };
            if ( this->keysDown[2] ) {
                for (auto &i : game.sprites) {
                    i->setY(i->y+(this->speed));
                }
            };
            if ( this->keysDown[3] ) {
                for (auto &i : game.sprites) {
                    i->setX(i->x+(this->speed));
                }
            };
        }
    }
}
