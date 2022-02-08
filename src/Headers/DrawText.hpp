#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class DrawText
{
public:
    static void drawText( short textX, short textY, const std::string& text, sf::RenderWindow& window, const sf::Texture& fontTexture );
};