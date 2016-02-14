#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include "Sprite.h"
#include "Player.h"
#include "Exit.h"
#include "Bullet.h"

class Game {
public:
    Game();
    ~Game(){};

    Player* player;
    Exit* levelExit;
    std::vector<Sprite*> sprites;
    std::list<Bullet*> bullets;
    char gameMap[64][128]; // [height][width]

    void update();
    void draw();
    void keyPress(unsigned char key);
    void keyRelease(unsigned char key);
    void mouseDown(int button, int state, int x, int y);
    void mouseMove(int x, int y);
    void createMap(int numRooms);
private:
    void addEnemy(float, float);
    void addWall(float, float);
};

#endif
