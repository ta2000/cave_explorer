#include "Wall.h"
#include "Game.h"

#include <GL/glut.h>

Wall::Wall(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
}
