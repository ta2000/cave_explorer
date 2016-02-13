#ifndef WALL_H
#define WALL_H

#include "Sprite.h"

class Wall : public Sprite {
public:
    Wall(float, float);
    ~Wall(){};

    float x,y,w,h;
private:

};

#endif
