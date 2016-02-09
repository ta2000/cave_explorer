#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
    Sprite(float, float);
    ~Sprite(){};

    float x,y,w,h;

    void draw();
private:

};

#endif
