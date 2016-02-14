#include "Sprite.h"
#include "Game.h"
#include "Exit.h"

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
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

void Sprite::update()
{
    // So we can call update on any sprite
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

    if (this->x < obj->x + 31 &&
		this->x + 31 > obj->x &&
		this->y < obj->y + 31 &&
		31 + this->y > obj->y) {
        collided = true;
    }

    return collided;
}

float Sprite::distance(Sprite* obj)
{
    float dx = abs((this->x+32/2) - (obj->x+32/2));
    float dy = abs((this->y+32/2) - (obj->y+32/2));
	float hyp = sqrt( (dx*dx)+(dy*dy) );

	return hyp;
}
