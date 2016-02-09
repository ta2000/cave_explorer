#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"

class Player : public Sprite {
public:
    Player(float, float);
    ~Player(){};

    float x,y,w,h;
private:

};

#endif
