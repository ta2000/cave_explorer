#include "Sprite.h"
#include "Game.h"
#include "Exit.h"

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#define PI 3.14159265359

extern Game game;

Sprite::Sprite(float x, float y)
{
    this->x = x;
    this->y = y;
    this->w = game.scale;
    this->h = game.scale;
    this->angle = 0.0; // Normal
}

void Sprite::setX(float value)
{
    this->x = value;
}

void Sprite::setY(float value)
{
    this->y = value;
}

void Sprite::setAngle(float value)
{
    this->angle = value;
}

float Sprite::getX()
{
    return this->x;
}

float Sprite::getY()
{
    return this->y;
}

float Sprite::getAngle()
{
    return this->angle;
}

void Sprite::update()
{
    // So we can call update on any sprite
}

void Sprite::draw()
{
    glPushMatrix();

        glTranslatef(x-(game.scale/2), y-(game.scale/2), 0.0f);
        glRotatef(angle*180/PI, 0.0f, 0.0f, 1.0f);
        glTranslatef(-x-(game.scale/2), -y-(game.scale/2), 0.0f);

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

    if (this->x < obj->x + obj->w-1 &&
		this->x + this->w-1 > obj->x &&
		this->y < obj->y + obj->h-1 &&
		this->y + this->h-1 > obj->y) {
        collided = true;
    }

    return collided;
}

bool Sprite::pointWithinSprite(float pointX, float pointY, Sprite* obj)
{
    bool within = false;

    if (pointX >= obj->x &&
        pointX <= obj->x + obj->w &&
        pointY >= obj->y &&
        pointY <= obj->y + obj->w)
    {
        within = true;
    }

    return within;
}

float Sprite::distance(Sprite* obj)
{
    float dx = abs((this->x+this->w/2) - (obj->x+obj->h/2));
    float dy = abs((this->y+this->h/2) - (obj->y+obj->h/2));
	float hyp = sqrt( (dx*dx)+(dy*dy) );

	return hyp;
}
