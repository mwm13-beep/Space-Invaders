#include <cmath>

#include "Headers/Bullet.hpp"
#include "Headers/Global.hpp"

Bullet::Bullet( short x, short y, float step_x, float step_y ):
x( x ),
y( y ),
real_x ( x ),
real_y ( y ),
step_x ( step_x ),
step_y ( step_y ),
inactive( false )
{}

/** update methods **/

//this checks if the player's bullet's have hit any enemies
void Bullet::update( std::vector<Enemy>& enemies )
{
    //update the bullet's position and check if it has left the screen
    moveAndCheckBounds();

    //check to see if the bullet is colliding with any enemies
    for ( int i = 0; i < enemies.size(); i++ )
    {
        //checking collision of the bullet's reduced size hit box versus the enemies reduced size hit box
        inactive = sf::IntRect( x + 0.375f * BASE_SIZE, y + 0.375f * BASE_SIZE, BASE_SIZE * 0.25f, BASE_SIZE * 0.25f ).intersects( sf::IntRect( enemies[i].getX(), enemies[i].getY(), BASE_SIZE * 0.5f, BASE_SIZE * 0.5f ) );

        //if the bullet was made inactive then it hit the enemy and the enemy should be removed
        if ( inactive )
        {
            enemies.erase( enemies.begin() + i );
            break; //this is important to prevent bullet's from killing more than one enemy
        }
    }
}

//this checks if the enemies bullets have hit the player
bool Bullet::update( unsigned short playerX, unsigned short playerY )
{
    //update the bullet's position and check if it has left the screen
    moveAndCheckBounds();

    //checking collision of the bullet's reduced size hit box versus the player's hit box
    inactive = sf::IntRect( x + 0.375f * BASE_SIZE, y + 0.375f * BASE_SIZE, BASE_SIZE * 0.25f, BASE_SIZE * 0.25f ).intersects( sf::IntRect( playerX, playerY, BASE_SIZE, BASE_SIZE ) );

    return inactive;
}

//private helper method for the update methods
void Bullet::moveAndCheckBounds()
{
    //update position
    real_x += step_x;
    real_y += step_y;
    x = std::round( real_x );
    y = std::round( real_y );

    //check to see if the bullet is out of bounds
    if ( x <= -BASE_SIZE || y <= -BASE_SIZE || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT )
    {
        inactive = true;
    }
}

void Bullet::render( sf::RenderWindow& window, sf::Sprite& sprite ) const
{
    sprite.setPosition( x, y );
    window.draw( sprite );
}

//accessors
bool Bullet::getStatus() const { return inactive; }
short Bullet::getX() const { return x; }
short Bullet::getY() const { return y; }




