#ifndef GUN_H
#define GUN_H

#include "Sprite.h"

#ifndef KEYSDOWN_SIZE
#define KEYSDOWN_SIZE 4
#endif

class Gun {
public:
    Gun(int, float, float);
    ~Gun(){};

    int fireRate, cooldown;
    float x,y,w,h, angle, damage, velocity;

    void fire();
    void update();
private:
};

#endif

