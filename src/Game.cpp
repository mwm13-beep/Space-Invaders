#include <SFML/Graphics.hpp>

#include "Headers/Game.hpp"
#include "Headers/Global.hpp"
#include "Headers/DrawText.hpp"


Game::Game():
player(),
enemyManager(),
startMenu ( true ),
endMenu( false )
{
    previous_time = std::chrono::steady_clock::now();
    lag = std::chrono::microseconds (0);
    fontTexture.loadFromFile( "src/Resources/font.png" );
};

void Game::run()
{
    sf::RenderWindow window( sf::VideoMode( SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT ), "Space Invaders", sf::Style::Close );
    window.setView( sf::View( sf::FloatRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ) ) );

    while ( window.isOpen() )
    {
        update( window ); //update game logic
        render( window ); //draw the updates
    }
}

void Game::update( sf::RenderWindow& window )
{
    //for checking events
    sf::Event event{};

    //get how much time has passed since the last loop iteration
    std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

    //tracks how far into a frame we are
    lag += delta_time;
    previous_time += delta_time;

    //random number generator initialization based on current clock time
    std::mt19937_64 randomEngine( std::chrono::system_clock::now().time_since_epoch().count() );

    while ( FRAME_DURATION <= lag )
    {
        //a frame has passed so we reset
        lag -= FRAME_DURATION;

        //allowing the user to exit any time
        while ( window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
            {
                window.close();
            }

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) )
            {
                startMenu = false;
            }

            if ( endMenu && sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) )
            {
                reset();
            }
        }

        //in this scenario the player has been defeated and so we print a message to the screen
        if ( !player.isDead() && enemyManager.enemiesLeft() != 0 && !startMenu && !enemyManager.getLanded() )
        {
            //player's game logic
            player.update( enemyManager.getEnemies() );

            //enemies' game logic
            enemyManager.update( player, randomEngine );
        }

        else if( player.isDead() || enemyManager.enemiesLeft() == 0 || enemyManager.getLanded() )
        {
            endMenu = true;
        }
    }
}

void Game::render( sf::RenderWindow& window )
{
    //draw the background
    window.clear( sf::Color( 0, 0, 0 ) ); //setting the background

    if ( startMenu )
    {
        DrawText::drawText( SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, "         ALIEN INVASION\n\n            Controls:\n    Left Arrow: moves left\n    Right Arrow: moves right\n    Space bar: shoots\n\nHit enter to start or esc to quit", window, fontTexture );
    }

    else if ( !player.isDead() && enemyManager.enemiesLeft() != 0 && !enemyManager.getLanded() )
    {
        //draw the player
        player.render( window );

        //render the enemies
        enemyManager.render( window );
    }

    else if ( player.isDead() )
    {
        DrawText::drawText( SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, "\n       You were destroyed!\n\n           Game Over :(\n\n     You destroyed " + std::to_string( INITIAL_ENEMIES - enemyManager.enemiesLeft()  ) + " aliens\n     Hit enter to play again\n         or esc to quit.", window, fontTexture );
    }

    else if ( enemyManager.enemiesLeft() == 0 )
    {
        DrawText::drawText( SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, "        You destroyed the \n\naliens and stopped the invasion!\n\n    Hit enter to play again\n         or esc to quit.", window, fontTexture );
    }

    else if ( enemyManager.getLanded() )
    {
        DrawText::drawText( SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, "\n   The aliens landed and invaded\n            the planet!\n\n           Game Over :(\n\n      You destroyed " + std::to_string( INITIAL_ENEMIES - enemyManager.enemiesLeft()  ) + " aliens\n     Hit enter to play again\n         or esc to quit.", window, fontTexture );
    }

    //display on the screen what has been rendered
    window.display();
}

void Game::reset()
{
    player.reset();
    enemyManager.reset();
    endMenu = false;
}

