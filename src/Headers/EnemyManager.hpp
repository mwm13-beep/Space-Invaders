#pragma once

#include <vector>
#include <random>

#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

class EnemyManager
{
    //stores enemies locations and status
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;

    //sprite for the enemies and their shots
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    sf::Texture enemyBulletTexture;
    sf::Sprite enemyBulletSprite;

    //movement variables
    unsigned short movePause;
    unsigned short moveTimer;
    unsigned short prevEnemyTotal; //this is a movement variable b/c the enemies update faster as more of them are killed

    //randomly deciding if enemies will shoot
    std::uniform_int_distribution<unsigned short> shootDistribution;

    //tracks if an enemy has landed
    bool landed;

public:
    EnemyManager();

    //update methods
    void update( Player& player, std::mt19937_64& randomEngine );
    void render( sf::RenderWindow &window );
    void reset();

    //accessors
    std::vector<Enemy>& getEnemies();
    unsigned int enemiesLeft();
    bool getLanded();

private:
    void enemySetUp();
};