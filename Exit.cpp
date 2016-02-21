#include "Exit.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

extern Game game;

Exit::Exit(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
}

void Exit::draw()
{
    glColor3f(0.6f, 0.0f, 0.8f);
    Sprite::draw();
}

bool Exit::update()
{
    game.levelNum++;
    if (collision(game.player))
    {
        // Delete all objects in sprites vector
        for (auto &i : game.sprites)
        {
            // If object's class is not an Exit, delete
            if (dynamic_cast<Exit*>(this) == NULL)
                delete i;
        }
        // Clear sprites
        game.sprites.clear(); // We still have a pointer to the level exit stored in game

        // Delete all bullets on screen
        for (auto &i : game.bullets)
        {
            delete i;
        }
        game.bullets.clear();

        // Create a new map
        game.createMap(10);
    }
    return true;
}
