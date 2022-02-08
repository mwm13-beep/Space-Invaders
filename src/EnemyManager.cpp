#include "Headers/EnemyManager.hpp"
#include "Headers/Global.hpp"

EnemyManager::EnemyManager() :
movePause ( ENEMY_MOVE_PAUSE_START ),
moveTimer ( ENEMY_MOVE_PAUSE_START ),
prevEnemyTotal ( INITIAL_ENEMIES ),
shootDistribution( 0, ENEMY_SHOOT_CHANCE ),
landed( false )
{
    enemyTexture.loadFromFile( "src/Resources/greenAlien.png" );
    enemySprite.setTexture( enemyTexture );

    enemyBulletTexture.loadFromFile( "src/Resources/enemyShot.png" );
    enemyBulletSprite.setTexture( enemyBulletTexture );

    enemySetUp();
};

void EnemyManager::update( Player& player, std::mt19937_64& randomEngine )
{
    /** enemy movement **/

    //if the enemies have waited for a full pause duration then we update them
    if ( moveTimer == 0 )
    {
        //reset the timer to the appropriate pause duration
        moveTimer = movePause;

        for ( Enemy& enemy: enemies )
        {
            enemy.update();

            if ( enemy.getLanded() )
            {
                landed = true;
            }
        }
    }

    //otherwise decrease the timer
    else
    {
        moveTimer--;
    }

    //update move pause to make the enemies update faster as more of them are killed
    //check to see if any enemies have been killed
    if ( prevEnemyTotal > enemies.size() )
    {
        //calculate how many enemies have been killed since the last update
        unsigned short enemiesKilled = prevEnemyTotal - enemies.size();

        //movePause is unsigned and so to prevent it from overflowing and effectively freezing the enemies in place
        //we set a min pause value and use the max function to enforce it
        movePause = std::max<int>( ENEMY_MOVE_PAUSE_MIN, movePause - ( ENEMY_MOVE_PAUSE_DECREASE * enemiesKilled ) );

        //update our prev total to ensure the next check is accurate
        prevEnemyTotal = enemies.size();
    }

    /** enemy shots **/

    //decide randomly for each enemy if they're going to shoot
    for ( Enemy& enemy: enemies )
    {
        if ( shootDistribution( randomEngine ) == 0 )
        {
            bullets.emplace_back( enemy.getX(), enemy.getY(), 0, ENEMY_BULLET_SPEED );
        }
    }

    //update and remove any bullets that have hit the player or gone out of bounds
    for ( int i = 0; i < bullets.size(); i++ )
    {
        //update, check out of bounds and collision
        bool playerHit = bullets[i].update( player.getX(), player.getY() );

        //mark the player as destroyed if they're hit
        if ( playerHit )
        {
            player.kill();
        }

        //remove if the bullet hit something or left the screen
        if ( bullets[i].getStatus() )
        {
            bullets.erase( bullets.begin() + i );
        }
    }
}

void EnemyManager::render( sf::RenderWindow &window )
{
    for ( Bullet& bullet : bullets )
    {
        bullet.render( window, enemyBulletSprite );
    }

    for ( Enemy& enemy : enemies )
    {
        enemy.render( window, enemySprite );
    }
}

//resets every thing to default values when the player wants to play again
void EnemyManager::reset()
{
    bullets.clear();
    enemies.clear();
    enemySetUp();
    prevEnemyTotal = INITIAL_ENEMIES;
    movePause = ENEMY_MOVE_PAUSE_START;
    moveTimer = ENEMY_MOVE_PAUSE_START;
    landed = false;
}

//private helper method for loading the initial enemy layout
void EnemyManager::enemySetUp()
{
    unsigned short init_x = SCREEN_WIDTH * 0.1f;
    unsigned short x = init_x;
    unsigned short y = SCREEN_HEIGHT * 0.1f - BASE_SIZE;

    //set the enemies up in a grid pattern
    for ( int i = 0; i < INITIAL_ENEMIES; i++ )
    {
        if ( i % ROW_LENGTH == 0 )
        {
            x = init_x; //at the end of the row go back to the left
            y += BASE_SIZE; //and go down a step
        }
        enemies.emplace_back( x, y );
        x += BASE_SIZE;
    }
}
std::vector<Enemy>& EnemyManager::getEnemies() { return enemies; }

unsigned int EnemyManager::enemiesLeft() { return enemies.size(); }

bool EnemyManager::getLanded() { return landed; }




