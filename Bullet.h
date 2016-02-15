#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet(float, float, float, float, float, float, float);
    ~Bullet(){};

    float x,y,radius,angle,damage,velocity,velX,velY;

    void update();
    void draw();
private:
};

#endif
