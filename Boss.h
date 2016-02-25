#ifndef BOSS_H
#define BOSS_H

#include "Sprite.h"
#include "Gun.h"

class Boss : public Sprite {
public:
    Boss(float, float);
    ~Boss(){};

    float x,y,w,h,angle,speed,targetX,targetY,hp;
    Gun* gun;

    bool activated = false;
    int phase = -1;
    int phaseCounter = 0;
    float shootingDirection = 0;

    void draw();
    bool update();
    void shoot(float, float, float);
private:

};

#endif


