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
    this->radius = game.scale/6;

    this->velX = velX/2;
    this->velY = velY/2;
    this->angle = angle;
    this->damage = damage;
    this->velocity = velocity;
    this->isEnemy = isEnemy;
}

void Bullet::update()
{
    x += (cos( angle )*velocity)+velX;
    y += (sin( angle )*velocity)+velY;
}

void Bullet::draw()
{
    glColor3f(0.3f, 0.3f, 1.0f);
	int triangleAmount = 10; //# of triangles used to draw circle

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


    glLineWidth(3);
    glColor3f(0.1f, 0.1f, 1.0f);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < triangleAmount; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(triangleAmount);//get the current angle

		float cx = radius * cosf(theta);//calculate the x component
		float cy = radius * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}
