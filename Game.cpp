#include "Game.h"

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"

#include <GL/glut.h>
#include <vector>

Game::Game()
{
    addEnemy(16.0f, 16.0f);
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


