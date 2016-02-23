#include "GunItem.h"
#include "Game.h"

#include <GL/glut.h>
#include <iostream>
#include <sstream>

extern Game game;

GunItem::GunItem(float x, float y, Gun* gun) : Sprite(x, y)
{
    this->x = x;
    this->y = y;
    this->gun = gun;
}

void GunItem::draw()
{
    glColor3f(1.0f, 1.0f, 0.0f);
    Sprite::draw();
    // Show this gun's stats
    if (distance(game.player) < game.scale*2)
    {
        std::ostringstream stat;

        stat << "ROF: " << (gun->fireRate);
        drawText(getX(), getY()+(game.scale/2), stat.str());
        stat.str(""); stat.clear();

        stat << "Damage: " << (gun->damage) << std::endl;
        drawText(getX(), getY()+2*(game.scale/2), stat.str());
        stat.str(""); stat.clear();

        stat << "Velocity: " << (gun->velocity);
        drawText(getX(), getY()+3*(game.scale/2), stat.str());
        stat.str(""); stat.clear();

    }
}

bool GunItem::update()
{
    bool unused = true;
    if (distance(game.player) < game.scale*2)
    {
        // Take gun if player presses e
        if (game.player->keysDown[4])
        {
            // Flag for deletion
            unused = false;
            // Delete the player's gun and set the pointer to this gun
            delete game.player->gun;
            game.player->gun = this->gun;
        }
    }
    return unused;
}


