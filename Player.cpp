#include "Player.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

Game game;

Player::Player(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
}

void Player::move()
{
    if (this->keysDown[0] == true) {
        for (auto &i : game.sprites) {
            i->setY(i->y+3);
        }
    }
    if (this->keysDown[1] == true) {
        for (auto &i : game.sprites) {
            i->setX(i->x+3);
        }
    }
    if (this->keysDown[2] == true) {
        for (auto &i : game.sprites) {
            i->setY(i->y-3);
        }
    }
    if (this->keysDown[3] == true) {
        for (auto &i : game.sprites) {
            i->setX(i->x-3);
        }
    }

    // Check collisions
    for (auto &i : game.sprites) {
        if (collision(i))
        {
            if ( this->keysDown[0] ) {
                for (auto &i : game.sprites) {
                    i->setY(i->y-3);
                }
            };
            if ( this->keysDown[1] ) {
                for (auto &i : game.sprites) {
                    i->setX(i->x-3);
                }
            };
            if ( this->keysDown[2] ) {
                for (auto &i : game.sprites) {
                    i->setY(i->y+3);
                }
            };
            if ( this->keysDown[3] ) {
                for (auto &i : game.sprites) {
                    i->setX(i->x+3);
                }
            };
        }
    }
}
