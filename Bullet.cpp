#include "Bullet.h"
#include "Game.h"

#include "Sprite.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265359

extern Game game;

Bullet::Bullet(float x, float y, float angle, float damage, float velocity, float velX, float velY, bool isEnemy)
{
    this->x = x;
    this->y = y;
    this->radius = game.scale/4;

    this->velX = velX;
    this->velY = velY;
    this->angle = angle;
    this->damage = damage;
    this->velocity = velocity;
    this->isEnemy = isEnemy;
}

bool Bullet::update()
{
    x += (cos( angle )*velocity)+velX;
    y += (sin( angle )*velocity)+velY;

    bool noHit = true;
    // Delete if off screen
    if ( x < 0 || x > glutGet(GLUT_WINDOW_WIDTH) || (y < 0 || y > glutGet(GLUT_WINDOW_HEIGHT)))
    {
        noHit = false;
    }
}

void Bullet::draw()
{
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(int i = 0; i <= triangleAmount;i++) {
			glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
