#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet(float, float, float, float, float, float, float, bool);
    ~Bullet(){};

    float x,y,radius,angle,damage,velocity,velX,velY;
    bool isEnemy;

    void update();
    void draw();
private:
};

#endif
