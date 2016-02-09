#include "Sprite.h"
#include "Game.h"

#include <GL/glut.h>

Sprite::Sprite(float x, float y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
}

void Sprite::draw()
{
    glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex2f(x, y);
            glVertex2f(x+w, y);
            glVertex2f(x+w, y+h);
            glVertex2f(x, y+h);
        glEnd();
	glPopMatrix();
}
