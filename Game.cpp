#include "Game.h"

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Exit.h"
#include "Health.h"

#include <GL/glut.h>
#include <iostream>

#include <stdlib.h> // For abs and random
#include <math.h> // For atan2
#include <time.h>   // Use time for seed

Game::Game()
{
    player = new Player(320 + scale/2, 240 + scale/2, 100, 10); // Screen width:height / 2 + (scale/2)
    levelExit = new Exit(0, 0);

    createMap(10);
}

void Game::createMap(int numRooms)
{
    srand(time(NULL));
    sprites.push_back(levelExit);

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

                // Add enemies and items to rooms, not including room 0 (player spawn)
                if (rooms != 0)
                {
                    // Enemy
                    if (gameMap[i][j] == ' ' && rand() % 20 == 0) // Frequency of enemies
                    {
                        gameMap[i][j] = 'm';
                    }
                }
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

    // Add the player in the first room
    gameMap[caveCoords[0][0]+1][caveCoords[0][1]+1] = 'p'; // Place the player 1 tile down and to the right of the first room

    // Add the exit to the last room
    gameMap[caveCoords[numRooms-1][0]+3][caveCoords[numRooms-1][1]+3] = 'e'; // Place the exit 3 tile down and to the right of the last room


    // ==============
    // CREATE OBJECTS
    // ==============
    float difY; // The y value to move all objects
    float difX; // The x value to move all objects

    for (unsigned int i=0; i<sizeof(gameMap)/sizeof(gameMap[0]); i++)
    {
        for (unsigned int j=0; j<sizeof(gameMap[0]); j++)
        {
            //std::cout << (gameMap[i][j]) << " ";
            if (gameMap[i][j] == 'x')
            {
                addWall(j*scale, i*scale);
            }
            else if (gameMap[i][j] == 'm')
            {
                addEnemy(j*scale, i*scale);
            }
            else if (gameMap[i][j] == 'e')
            {
                levelExit->setX(j*scale);
                levelExit->setY(i*scale);
            }
            else if (gameMap[i][j] == 'p')
            {
                // Set the view on the player
                difX = j*scale - player->x;
                difY = i*scale - player->y;
            }

        }
        std::cout << std::endl;
    }

    // Center the view on the player by moving all other objects
    for (auto &i : sprites)
    {
        i->x -= difX;
        i->y -= difY;
    }
}

void Game::update()
{
    player->update();
    levelExit->update();

    for (auto i = sprites.begin(); i != sprites.end();)
    {
        if ((*i)->update() == false)
        {
            delete(*i);
            sprites.erase(i);
        }
        ++i;
    }

    // Update all bullets
    for (auto i = bullets.begin(); i != bullets.end();)
    {
        (*i)->update();
        // Delete if off screen
        if ( (*i)->x < 0 || (*i)->x > glutGet(GLUT_WINDOW_WIDTH) || (*i)->y < 0 || (*i)->y > glutGet(GLUT_WINDOW_HEIGHT))
        {
            // Delete the bullet pointed to
            delete (*i);
            // Remove the pointer from the list
            bullets.erase(i);
        }
        ++i;
    }
}

// Draw all objects in the sprites vector
void Game::draw()
{
    for (auto &i : bullets)
    {
        i->draw();
    }

    for (auto i = sprites.begin(); i != sprites.end();)
    {
        if ((*i)->distance(player) < glutGet(GLUT_WINDOW_WIDTH))
        {
            (*i)->draw();
            glColor3f(0.3f, 0.1f, 0.0f);
        }
        ++i;
    }

    levelExit->draw();
    player->draw();
}

// Add a new wall object to the array of sprites
void Game::addWall(float x, float y)
{
    sprites.push_back(new Wall(x, y));
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
        case 'e':
            player->keysDown[4] = true;
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
        case 'e':
            player->keysDown[4] = false;
            break;
    }
    glutPostRedisplay();
}

void Game::mouseDown(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        player->mouse = true;
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        player->mouse = false;
}

void Game::mouseMove(int x, int y)
{
    player->setAngle(atan2(y - player->y, x - player->x));
}
