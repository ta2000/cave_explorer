#include "Health.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

extern Game game;

Health::Health(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->restoreAmount = rand() % 10 + game.levelNum*2;
}

void Health::draw()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    Sprite::draw();
}

bool Health::update()
{
    bool unused = true;
    if (collision(game.player))
    {
        unused = false;
        game.player->hp += restoreAmount;
        // Prevent player from having more than max health
        if (game.player->hp > game.player->maxHp)
        {
            game.player->hp = game.player->maxHp;
        }
    }
    return unused;
}

