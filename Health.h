#ifndef HEALTH_H
#define HEALTH_H

#include "Sprite.h"

class Health : public Sprite {
public:
    Health(float, float);
    ~Health(){};

    float x,y,w,h;
    int restoreAmount;

    void draw();
    bool update();
private:
};

#endif

