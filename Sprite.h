#ifndef SPRITE_H
#define SPRITE_H

#include "Bullet.h"
#include <iostream>

class Sprite {
public:
    Sprite(float, float);
    virtual ~Sprite(){};

    float x,y,w,h,angle;

    void setW(float value);
    void setH(float value);
    void setX(float value);
    void setY(float value);
    void setAngle(float value);
    float getW();
    float getH();
    float getX();
    float getY();
    float getAngle();

    virtual bool update();
    virtual void draw();
    void drawText(float x, float y, std::string text);
    bool collision(Sprite* obj);
    bool bulletCollision(Bullet* obj);
    bool pointWithinSprite(float pointX, float pointY, Sprite* obj);
    float distance(Sprite* obj);
private:
};

#endif
