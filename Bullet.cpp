#include "Bullet.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265359

Bullet::Bullet(float x, float y, float direction, float damage, float spread)
{
    this->x = x;
    this->y = y;
    this->radius = 8;

    this->direction = direction;
    this->damage = damage;
    this->spread = spread;
}

void Bullet::update()
{

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
