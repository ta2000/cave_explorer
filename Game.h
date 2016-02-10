#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Sprite.h"
#include "Player.h"

class Game {
public:
    Game();
    ~Game(){};

    Player* player;
    std::vector<Sprite*> sprites;

    void update();
    void draw();
    void keyPress(unsigned char key);
    void keyRelease(unsigned char key);
private:
    void addEnemy(float, float);
};

#endif
