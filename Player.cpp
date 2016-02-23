#include "Player.h"
#include "Game.h"
#include "Wall.h"
#include "Gun.h"

#include <GL/glut.h>
#include <iostream>
#include <sstream>

Game game;

Player::Player(float x, float y, float hp, float speed) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->trueX = x;
    this->trueY = y;
    this->gun = (new Gun(40, 10, 1, false)); // ROF, DMG, VEL
    this->angle = 0;
    this->hp = hp;
    this->maxHp = hp;
    this->speed = speed;
}

void Player::shoot(float velX, float velY)
{
    game.bullets.push_back( new Bullet(getX()-game.scale/2, getY()-game.scale/2, getAngle(), gun->damage, gun->velocity+12, velX, velY, false) );
    gun->cooldown = gun->fireRate;
}

void Player::draw()
{
    glColor3f(0.0f, 0.3f, 0.0f);
    Sprite::draw();
    // Draw health bar
    glPushMatrix();
        // Create string with levelNum inside using oss
        std::ostringstream levelString;
        levelString << "Level: " << game.levelNum;
        drawText(maxHp+40, 32, levelString.str());
        // Border
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex2f(20-5, 10-5);
            glVertex2f(20+maxHp+5, 10-5);
            glVertex2f(20+maxHp+5, 10+32+5);
            glVertex2f(20-5, 10+32+5);
        glEnd();

        // Health lost
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex2f(20, 10);
            glVertex2f(20+maxHp, 10);
            glVertex2f(20+maxHp, 10+32);
            glVertex2f(20, 10+32);
        glEnd();

        // Health
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex2f(20, 10);
            glVertex2f(20+hp, 10);
            glVertex2f(20+hp, 10+32);
            glVertex2f(20, 10+32);
        glEnd();
    glPopMatrix();
}

bool Player::update()
{
    float prevX = trueX;
    float prevY = trueY;

    // Movement
    if (this->keysDown[0] == true) {
        trueY -= speed;
        for (auto &i : game.sprites) {
            i->setY(i->y+(this->speed));
        }
        for (auto &i : game.bullets) {
            i->y+=this->speed;
        }
    }
    if (this->keysDown[1] == true) {
        trueX -= speed;
        for (auto &i : game.sprites) {
            i->setX(i->x+(this->speed));
        }
        for (auto &i : game.bullets) {
            i->x+=this->speed;
        }
    }
    if (this->keysDown[2] == true) {
        trueY += speed;
        for (auto &i : game.sprites) {
            i->setY(i->y-(this->speed));
        }
        for (auto &i : game.bullets) {
            i->y-=this->speed;
        }
    }
    if (this->keysDown[3] == true) {
        trueX += speed;
        for (auto &i : game.sprites) {
            i->setX(i->x-(this->speed));
        }
        for (auto &i : game.bullets) {
            i->x-=this->speed;
        }
    }

    // Check collisions
    for (auto &i : game.sprites) {
        if (collision(i) && dynamic_cast<Wall*>(i) != NULL) // Only collide if wall
        {
            if ( this->keysDown[0] ) {
                trueY += speed;
                for (auto &i : game.sprites) {
                    i->setY(i->y-(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->y-=this->speed;
                }
            };
            if ( this->keysDown[1] ) {
                trueX += speed;
                for (auto &i : game.sprites) {
                    i->setX(i->x-(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->x-=this->speed;
                }
            };
            if ( this->keysDown[2] ) {
                trueY -= speed;
                for (auto &i : game.sprites) {
                    i->setY(i->y+(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->y+=this->speed;
                }
            };
            if ( this->keysDown[3] ) {
                trueX -= speed;
                for (auto &i : game.sprites) {
                    i->setX(i->x+(this->speed));
                }
                for (auto &i : game.bullets) {
                    i->x+=this->speed;
                }
            };
        }
    }

    // Shooting
    if (gun != nullptr)
    {
        // Update gun
        gun->update();
        // Shoot
        if (mouse == true && gun->cooldown <= 0)
        {
            shoot((trueX - prevX), (trueY - prevY));
        }
    }

    // Check if hit by enemy bullet
    for (auto i = game.bullets.begin(); i != game.bullets.end();)
    {
        if (bulletCollision(*i) && (*i)->isEnemy==true)
        {
            hp -= (*i)->damage;
            delete (*i);
            game.bullets.erase(i++);
        }
        ++i;
    }

    // Check if dead or not
    if (hp <= 0)
    {
        game.levelExit->setX(x);
        game.levelExit->setY(y);
        hp = maxHp;
        game.levelNum = 0;
    }

    return true;
}
