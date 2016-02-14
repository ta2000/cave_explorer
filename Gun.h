#ifndef GUN_H
#define GUN_H

#include "Sprite.h"

#ifndef KEYSDOWN_SIZE
#define KEYSDOWN_SIZE 4
#endif

class Gun : public Sprite {
public:
    Gun(float, float, int, int, int);
    ~Gun(){};

    int fireRate, cooldown,damage,spread;
    float x,y,w,h,rotation;

    void fire();
    void update();
private:
};

#endif

