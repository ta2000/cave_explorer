#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"
#include "Gun.h"

#ifndef KEYSDOWN_SIZE
#define KEYSDOWN_SIZE 4
#endif

class Player : public Sprite {
public:
    Player(float, float, float, float);
    ~Player(){};

    float x,y,trueX,trueY,w,h,speed,angle,hp,maxHp;
    bool keysDown[KEYSDOWN_SIZE] = {false, false, false, false};
    bool mouse = false;
    Gun* gun;

    void draw();
    bool update();
    void shoot(float, float);
private:
};

#endif
