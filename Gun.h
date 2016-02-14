#ifndef GUN_H
#define GUN_H

#include "Sprite.h"

#ifndef KEYSDOWN_SIZE
#define KEYSDOWN_SIZE 4
#endif

class Gun : public Sprite {
public:
    Gun(float, float);
    ~Gun(){};

    float x,y,w,h,rotation,damage,fireRate,spread;
private:
};

#endif

