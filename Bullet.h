#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"

class Bullet : public Sprite {
public:
    Bullet(float, float, float, float, float, float, float);
    ~Bullet(){};

    float x,y,radius,angle,damage,velocity,velX,velY;

    void update();
    void draw();
private:
};

#endif
