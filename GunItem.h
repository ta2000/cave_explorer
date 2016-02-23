#ifndef GUNITEM_H
#define GUNITEM_H

#include "Sprite.h"
#include "Gun.h"

class GunItem : public Sprite {
public:
    GunItem(float, float, Gun*);
    ~GunItem(){};

    float x,y,w,h;
    Gun* gun;

    void draw();
    bool update();
private:
};

#endif


