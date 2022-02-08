#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

class Bullet
{
    //position variables
    short x;
    short y;
    float real_x;
    float real_y;
    float step_x;
    float step_y;

    //marks if the bullet has hit something or gone out of bounds
    bool inactive;

public:
    Bullet( short x, short y, float step_x, float step_y );

    //update methods
    void update( std::vector<Enemy>& enemies );
    bool update( unsigned short x, unsigned short y );
    void render( sf::RenderWindow& window, sf::Sprite& bulletSprite ) const;

    //accessors
    bool getStatus() const;
    short getX() const;
    short getY() const;

private:
    void moveAndCheckBounds();
};
