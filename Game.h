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

    void draw();

private:
    void addEnemy(float, float);
};

#endif
