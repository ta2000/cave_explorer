#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
    Sprite(float, float);
    virtual ~Sprite(){};

    float x,y,w,h,angle;

    void setX(float value);
    void setY(float value);
    void setAngle(float value);
    float getX();
    float getY();
    float getAngle();

    virtual void update();
    void draw();
    bool collision(Sprite* obj);
    float distance(Sprite* obj);
private:
};

#endif
