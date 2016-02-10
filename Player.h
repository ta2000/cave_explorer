#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

#ifndef KEYSDOWN_SIZE
#define KEYSDOWN_SIZE 4
#endif

class Player : public Sprite {
public:
    Player(float, float);
    ~Player(){};

    float x,y,w,h;
    bool keysDown[KEYSDOWN_SIZE] = {false, false, false, false};

    void move();
private:
};

#endif
