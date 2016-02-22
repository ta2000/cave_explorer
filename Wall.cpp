#include "Wall.h"
#include "Game.h"

#include <GL/glut.h>

Wall::Wall(float x, float y) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
}

void Wall::draw()
{
    glColor3f(0.3, 0.1, 0.0);
    Sprite::draw();
}
