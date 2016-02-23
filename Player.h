#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"
#include "Gun.h"

class Player : public Sprite {
public:
    Player(float, float, float, float);
    ~Player(){};

    float x,y,trueX,trueY,w,h,speed,angle,hp,maxHp;
    bool keysDown[5] = {false, false, false, false, false}; // W,A,S,D,E
    bool mouse = false;
    Gun* gun;

    void draw();
    bool update();
    void shoot(float, float);
private:
};

#endif
