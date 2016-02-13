#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
    Sprite(float, float);
    ~Sprite(){};

    float x,y,w,h;

    void setX(float value);
    void setY(float value);
    void draw();
    bool collision(Sprite* obj);
private:
};

#endif
