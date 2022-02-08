#include <SFML/Graphics.hpp>
#include <cmath>

#include "Headers/Enemy.hpp"
#include "Headers/Global.hpp"

Enemy::Enemy( unsigned short x, unsigned short y ):
x( x ),
y( y ),
direction ( ( y / BASE_SIZE ) % 2 == 0 ? left : right ),
landed ( false )
{}

void Enemy::render( sf::RenderWindow &window, sf::Sprite sprite ) const
{
    sprite.setPosition( x, y );
    window.draw( sprite );
}

void Enemy::update()
{
    //if the enemy isn't moving down then it needs to decide if its travelling left or right
    if ( direction != down )
    {
        //check if at the edge of the screen and if we are update down
        if ( ( direction == right && x == SCREEN_WIDTH - BASE_SIZE ) || ( direction == left && x == 0 ) )
        {
            direction = down;
            y += ENEMY_MOVE_SPEED;
        }

        //otherwise continue moving horizontally
        else
        {
            x = std::clamp<short>( x + ENEMY_MOVE_SPEED * direction, 0, SCREEN_WIDTH - BASE_SIZE );
        }
    }

    //in this case the enemy is moving down and so we need to update them down a specific height
    else
    {
        //let the enemy update 2 pixels down until they've moved 16 pixels then stop them at that new height
        y = std::min<short>( y + ENEMY_MOVE_SPEED, BASE_SIZE * std::ceil( y / static_cast<float>( BASE_SIZE ) ) );

        //check if we've moved down 16 pixels and change the direction if we have
        if ( y == BASE_SIZE * std::ceil( y / static_cast<float>( BASE_SIZE ) ) )
        {
            //even number of base_size units from the top means go left, odd number means go right
            direction = ( 0 == ( y / BASE_SIZE ) % 2 ) ? left : right;
        }
    }

    //check if the enemy has reached the ground
    if ( y + BASE_SIZE >= SCREEN_HEIGHT * 0.9f )
    {
        landed = true;
    }
}

unsigned short Enemy::getX() const { return x; }
unsigned short Enemy::getY() const { return y; }
bool Enemy::getLanded() const { return landed; }


