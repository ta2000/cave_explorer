#include "Game.h"

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

#include <GL/glut.h>
#include <iostream>
#include <vector>

#include <stdlib.h> // For math and random
#include <time.h>   // Use time for seed

Game::Game()
{
    player = new Player(304, 224, 8); // Screen width:height / 2 - (scale/2)

    createMap(10);

    for (unsigned int i=0; i<sizeof(gameMap)/sizeof(gameMap[0]); i++)
    {
        for (unsigned int j=0; j<sizeof(gameMap[0]); j++)
        {
            std::cout << (gameMap[i][j]) << " ";
            if (gameMap[i][j] == 'x')
            {
                addWall(j*32, i*32);
            }

        }
        std::cout << std::endl;
    }
}

void Game::createMap(int numRooms)
{
    srand(time(NULL));

    // ============
    // CREATE ROOMS
    // ============
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
    int caveCoords[numRooms][2];
    for (int rooms=0; rooms<numRooms; rooms++)
    {
        // Generate room with random dimensions and location
        room_width = rand() % 4 + 8;
        room_height = rand() % 4 + 8;
        room_x = rand() % sizeof(gameMap[0]) + 1;
        room_y = rand() % sizeof(gameMap)/sizeof(gameMap[0]) + 1;

        // Prevent the room dimensions from exceeding map size
        if ( (room_x + room_width) > sizeof(gameMap[0]) )
        {
            room_x = ( sizeof(gameMap[0]) - room_width );
        }
        if ( (room_y + room_height) > sizeof(gameMap)/sizeof(gameMap[0]) )
        {
            room_y = ( sizeof(gameMap)/sizeof(gameMap[0]) - room_height );
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
            startY = caveCoords[i+1][0]+2; // +2 prevents offset on left-up paths

        // Horizontal tunnels
        for (int j=startX; j<abs((caveCoords[i][1])-(caveCoords[i+1][1]))+startX+1; j++)
        {
            gameMap[caveCoords[i][0]][j] = ' ';
            gameMap[caveCoords[i][0]+1][j] = ' ';
            gameMap[caveCoords[i][0]+2][j] = ' ';
        }
        // Vertical tunnels
        for (int j=startY; j<abs((caveCoords[i][0])-(caveCoords[i+1][0]))+startY+1; j++)
        {
            gameMap[j][caveCoords[i+1][1]] = ' ';
            gameMap[j][caveCoords[i+1][1]+1] = ' ';
            gameMap[j][caveCoords[i+1][1]+2] = ' ';
        }
    }


    // ==============
    // CREATE ENEMIES
    // ==============
    /*for (unsigned int i=0; i<sizeof(gameMap)/sizeof(gameMap[0]); i++)
    {
        for (unsigned int j=0; j<sizeof(gameMap[0]); j++)
        {
            if (gameMap[i][j] == ' ' && rand() % 10 == 0) // Frequency of enemies
            {
                gameMap[i][j] = 'e';
            }
        }
    }*/

}

void Game::update()
{
    player->move();
}

// Draw all objects in the sprites vector
void Game::draw()
{
    player->draw();
    for (auto &i : sprites) {
        if (i->distance(player) < glutGet(GLUT_WINDOW_WIDTH))
        {
            i->draw();
        }
    }
}

// Add a new enemy object to the array of sprites
void Game::addEnemy(float x, float y)
{
    sprites.push_back(new Enemy(x, y));
}
// Add a new wall object to the array of sprites
void Game::addWall(float x, float y)
{
    sprites.push_back(new Wall(x, y));
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
