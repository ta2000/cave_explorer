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

    // Attacking AI
    int attackMovement = 0;
    int attackMovementCounter = 1;
    int mixedDirections[4] = {0,1,2,3};
    // Wandering AI
    int wanderingDirection = 0;

    bool update();
private:

};

#endif

