#include "Headers/DrawText.hpp"

void DrawText::drawText( short textX, short textY, const std::string &text, sf::RenderWindow &window, const sf::Texture &fontTexture)
{
    short charX = textX;
    short charY = textY;

    unsigned char charHeight = fontTexture.getSize().y;
    unsigned char charWidth = fontTexture.getSize().x / 96; //there are 96 characters in the font pack I'm using

    sf::Sprite characterSprite( fontTexture );

    for ( std::string::const_iterator curr = text.begin(); curr != text.end(); curr++ )
    {
        //go to the next row if we encounter a new line char
        if( '\n' == *curr )
        {
            charX = textX; //back to the initial x value
            charY += textY; //down to the new row
        }

        //
        else
        {
            characterSprite.setPosition( charX, charY );
            characterSprite.setTextureRect( sf::IntRect( charWidth * (*curr - 32 ), 0, charWidth, charHeight ) );
            charX += charWidth;
            window.draw( characterSprite );
        }
    }
}
