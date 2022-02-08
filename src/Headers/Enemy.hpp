#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
    //where the enemy is on the screen
    unsigned short x;
    unsigned short y;

    //whether the enemy is moving left, right or down
    enum directions { left = -1, down = 0, right = 1 };
    char direction;

    //tracks if the enemy is dead or not
    bool landed;

public:
    Enemy( unsigned short x, unsigned short y );

    //update methods
    void render( sf::RenderWindow &window, sf::Sprite sprite ) const;
    void update();

    //accessors
    unsigned short getX() const;
    unsigned short getY() const;
    bool getLanded() const;
};
