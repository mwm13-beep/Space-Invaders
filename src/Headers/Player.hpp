#pragma once

#include "Bullet.hpp"
#include "Enemy.hpp"

class Player
{
    //what the drawable will look like
    sf::Texture texture;
    sf::Sprite sprite;

    //what the player's shots will look like
    sf::Texture shotTexture;
    sf::Sprite shotSprite;

    //track the player's shots
    std::vector<Bullet> bullets;
    unsigned char reloadTimer;

    //where the drawable is
    unsigned short x;
    unsigned short y;

    //tracks if the player has been killed or not
    bool dead;
    bool aliensLanded;

public:
    Player();

    //update methods
    void render( sf::RenderWindow& window );
    void update( std::vector<Enemy>& enemies );
    void kill();
    void reset();

    //accessors
    unsigned short getX() const;
    unsigned short getY() const;
    bool isDead() const;
};
