#ifndef EXIT_H
#define EXIT_H

#include "Sprite.h"

class Exit : public Sprite {
public:
    Exit(float, float);
    ~Exit(){};

    float x,y,w,h;

    virtual void update();
private:
};

#endif

