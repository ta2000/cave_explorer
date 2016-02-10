#include "Game.h"

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"

#include <GL/glut.h>
#include <vector>

Game::Game()
{
    player = new Player(64, 64);
    sprites.push_back(player);
    addEnemy(16.0f, 16.0f);
}

void Game::update()
{
    player->move();
}

void Game::draw()
{
    for (auto &i : sprites) {
        i->draw();
    }
}

void Game::addEnemy(float x, float y)
{
    sprites.push_back(new Enemy(x, y));
}


void Game::keyPress(unsigned char key)
{
    switch(key) {
        case 'w':
            player->keysDown[0] = true;
            break;
        case 'a':
            player->keysDown[1] = true;
            break;
        case 's':
            player->keysDown[2] = true;
            break;
        case 'd':
            player->keysDown[3] = true;
            break;
        case 27: // Escape
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void Game::keyRelease(unsigned char key)
{
    switch(key) {
       case 'w':
            player->keysDown[0] = false;
            break;
       case 'a':
            player->keysDown[1] = false;
            break;
       case 's':
            player->keysDown[2] = false;
           break;
       case 'd':
            player->keysDown[3] = false;
           break;
       case 32: // Space

           break;
   }
   glutPostRedisplay();
}
