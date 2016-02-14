#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
    Sprite(float, float);
    virtual ~Sprite(){}; // NEED TO DELETE PROPERTIES?

    float x,y,w,h;

    void setX(float value);
    void setY(float value);
    virtual void update();
    void draw();
    bool collision(Sprite* obj);
    float distance(Sprite* obj);
private:
};

#endif
