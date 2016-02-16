#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "Gun.h"

class Enemy : public Sprite {
public:
    Enemy(float, float);
    ~Enemy(){};

    float x,y,w,h,angle,speed,targetX,targetY;
    Gun* gun;

    void update();
private:

};

#endif

