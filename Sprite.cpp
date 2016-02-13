#include "Sprite.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>

Sprite::Sprite(float x, float y)
{
    this->x = x;
    this->y = y;
    this->w = 32;
    this->h = 32;
}

void Sprite::setX(float value)
{
    this->x = value;
}

void Sprite::setY(float value)
{
    this->y = value;
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

bool Sprite::collision(Sprite* obj)
{
    bool collided = false;

    if (this->x < obj->x + 32 &&
		this->x + 32 > obj->x &&
		this->y < obj->y + 32 &&
		32 + this->y > obj->y) {
        collided = true;
    }

    return collided;
}
