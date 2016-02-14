#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Sprite.h"
#include "Player.h"
#include "Exit.h"

class Game {
public:
    Game();
    ~Game(){};

    Player* player;
    Exit* levelExit;
    std::vector<Sprite*> sprites;
    char gameMap[64][128]; // [height][width]

    void update();
    void draw();
    void keyPress(unsigned char key);
    void keyRelease(unsigned char key);
    void createMap(int numRooms);
private:
    void addEnemy(float, float);
    void addWall(float, float);
};

#endif
