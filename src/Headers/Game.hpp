#pragma once

#include <chrono>
#include "Player.hpp"
#include "EnemyManager.hpp"

class Game
{
    std::chrono::steady_clock::time_point previous_time;
    std::chrono::microseconds lag{};

    Player player;
    EnemyManager enemyManager;
    bool startMenu;
    bool endMenu;

    sf::Texture fontTexture;
public:
    Game();
    void run();
    void update( sf::RenderWindow& window );
    void render( sf::RenderWindow& window );
    void reset();
};