#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"

class Enemy : public Sprite {
public:
    Enemy(float, float);
    ~Enemy(){};

    float x,y,w,h;
private:

};

#endif

