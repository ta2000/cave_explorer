#include "Game.h"

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"

#include <GL/glut.h>
#include <iostream>
#include <vector>

#include <stdlib.h> // For math and random
#include <time.h>   // Use time for seed

Game::Game()
{
    player = new Player(64, 64);
    sprites.push_back(player);
    addEnemy(16.0f, 16.0f);

    createMap();

    for (unsigned int i=0; i<sizeof(gameMap)/sizeof(gameMap[0]); i++)
    {
        for (unsigned int j=0; j<sizeof(gameMap[0]); j++)
        {
            std::cout << (gameMap[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Game::createMap()
{
    srand(time(NULL));

    unsigned int room_x, room_y, room_width, room_height;

    // Fill map with blocked
    for (unsigned int i=0; i<sizeof(gameMap)/sizeof(gameMap[0]); i++)
    {
        for (unsigned int j=0; j<sizeof(gameMap[0]); j++)
        {
            gameMap[i][j] = 'x';
        }
    }

    // Create rooms
    int caveCoords[10][2];
    for (int rooms=0; rooms<10; rooms++)
    {
        // Generate room with random dimensions and location
        room_width = rand() % 3 + 3;
        room_height = rand() % 3 + 3;
        room_x = rand() % sizeof(gameMap[0]) + 1;
        room_y = rand() % sizeof(gameMap)/sizeof(gameMap[0]) + 1;

        // Prevent the room dimensions from exceeding map size
        if ( (room_x + room_width) > sizeof(gameMap[0]) )
        {
            room_x -= ( sizeof(gameMap[0]) - room_width );
        }
        if ( (room_y + room_height) > sizeof(gameMap)/sizeof(gameMap[0]) )
        {
            room_y -= ( sizeof(gameMap)/sizeof(gameMap[0]) - room_height );
        }

        // Save coords of rooms to array
        caveCoords[rooms][0] = room_y;
        caveCoords[rooms][1] = room_x;

        // Clear out room
        for (unsigned int i=room_y; i<(room_y + (room_height-1)); i++)
        {
            for (unsigned int j=room_x; j<(room_x + (room_width-1)); j++)
            {
                gameMap[i][j] = ' ';
            }
        }
    }

    // Add tunnels connecting rooms
    for (unsigned int i=0; i<sizeof(caveCoords)/sizeof(caveCoords[0])-1; i++)
    {
        // Horizontal tunnels
        int startX; // Determine which room is farthest left
        if (caveCoords[i][1] < caveCoords[i+1][1])
            startX = caveCoords[i][1];
        else
            startX = caveCoords[i+1][1];

        // Vertical tunnels
        int startY; // Determine which room is farthest up
        if (caveCoords[i][0] < caveCoords[i+1][0])
            startY = caveCoords[i][0];
        else
            startY = caveCoords[i+1][0];

        // Horizontal tunnels
        std::cout << "[" << (caveCoords[i][1]) << ", " << (caveCoords[i][0]) << "] [" << (caveCoords[i+1][1]) << ", " << (caveCoords[i+1][0]) << "]" << std::endl;
        for (int j=startX; j<abs((caveCoords[i][1])-(caveCoords[i+1][1]))+startX+1; j++)
        {
            gameMap[caveCoords[i][0]][j] = ' ';
        }

        for (int j=startY; j<abs((caveCoords[i][0])-(caveCoords[i+1][0]))+startY+1; j++)
        {
            gameMap[j][caveCoords[i+1][1]] = ' ';
        }
    }

}

void Game::update()
{
    player->move();
}

// Draw all objects in the sprites vector
void Game::draw()
{
    for (auto &i : sprites) {
        i->draw();
    }
}

// Add a new enemy object to the array of sprites
void Game::addEnemy(float x, float y)
{
    sprites.push_back(new Enemy(x, y));
}

// Move the player based on keyboard input
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
   }
   glutPostRedisplay();
}
