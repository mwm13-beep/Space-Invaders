#include <SFML/Graphics.hpp>

#include "Headers/Player.hpp"
#include "Headers/Global.hpp"


Player::Player() :
x ( SCREEN_WIDTH * 0.5f),
y ( SCREEN_HEIGHT * 0.90f ),
reloadTimer(0),
dead ( false ),
aliensLanded ( false )
{
    texture.loadFromFile( "src/Resources/player.png" );
    sprite.setTexture( texture );

    shotTexture.loadFromFile( "src/Resources/playerShot.png" );
    shotSprite.setTexture( shotTexture );
}

void Player::render( sf::RenderWindow &window )
{
    sprite.setPosition( x, y );

    for ( Bullet& bullet : bullets )
    {
        bullet.render( window, shotSprite );
    }

    window.draw( sprite );
}

void Player::update( std::vector<Enemy>& enemies )
{
    //update left
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        //cleaner to use the built in max/min functions than to write an if statement that does the same
        x = std::max<int>( x - PLAYER_SPEED, 0 );
    }

    //update right
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
    {
        x = std::min<int>( x + PLAYER_SPEED, SCREEN_WIDTH - BASE_SIZE );
    }

    //shoot
    if ( reloadTimer == 0 )
    {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
        {
            bullets.emplace_back( x, y, 0, -PLAYER_BULLET_SPEED );
            reloadTimer = PLAYER_RELOAD_TIME;
        }
    }

    //or wait for reload
    else
    {
        reloadTimer--;
    }

    //update bullets and remove those marked as inactive
    for ( int i = 0; i < bullets.size(); i++ )
    {
        bullets[i].update( enemies );

        if ( bullets[i].getStatus() )
        {
            bullets.erase( bullets.begin() + i );
        }
    }
}

void Player::kill() { dead = true; }

void Player::reset()
{
    dead = false;
    bullets.clear();
    x = SCREEN_WIDTH * 0.5f;
    y = SCREEN_HEIGHT * 0.90f;
}

//accessors
unsigned short Player::getX() const { return x; }
unsigned short Player::getY() const { return y; }
bool Player::isDead() const { return dead; }

