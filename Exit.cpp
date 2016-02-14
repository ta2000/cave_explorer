#include "Exit.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

extern Game game;

Exit::Exit(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
}

void Exit::update()
{
    if (collision(game.player))
    {
        // Delete all objects in sprites vector
        for (unsigned int i=0; i<game.sprites.size(); i++)
        {
            // If object's class is not an Exit, delete
            if (dynamic_cast<Exit*>(this) == NULL)
                delete game.sprites[i];
        }
        // Clear sprites
        game.sprites.clear(); // We still have a pointer to the level exit stored in game
        // Create a new map
        game.createMap(10);
    }
}
