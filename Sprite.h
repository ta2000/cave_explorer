#ifndef SPRITE_H
#define SPRITE_H

#include "Bullet.h"

class Sprite {
public:
    Sprite(float, float);
    virtual ~Sprite(){};

    float x,y,w,h,angle;

    void setX(float value);
    void setY(float value);
    void setAngle(float value);
    float getX();
    float getY();
    float getAngle();

    virtual bool update();
    void draw();
    bool collision(Sprite* obj);
    bool bulletCollision(Bullet* obj);
    bool pointWithinSprite(float pointX, float pointY, Sprite* obj);
    float distance(Sprite* obj);
private:
};

#endif
