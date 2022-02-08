#pragma once

#include <chrono>
//sprite constants
constexpr unsigned char BASE_SIZE = 16;

//player constants
constexpr unsigned char PLAYER_SPEED = 2;
constexpr unsigned char PLAYER_BULLET_SPEED = 3;
constexpr unsigned char PLAYER_RELOAD_TIME = 20;

//screen constants
constexpr unsigned char SCREEN_RESIZE = 4;
constexpr unsigned short SCREEN_HEIGHT = 180;
constexpr unsigned short SCREEN_WIDTH = 320;

//enemy constants
constexpr unsigned short INITIAL_ENEMIES = 64;
constexpr unsigned short ROW_LENGTH = 16;
constexpr unsigned short ENEMY_MOVE_PAUSE_START = 110;
constexpr unsigned short ENEMY_MOVE_PAUSE_DECREASE = 2;
constexpr unsigned short ENEMY_MOVE_PAUSE_MIN = 0;
constexpr unsigned short ENEMY_MOVE_SPEED = 2;
constexpr unsigned short ENEMY_SHOOT_CHANCE = 512;
constexpr unsigned short ENEMY_BULLET_SPEED = 2;

constexpr std::chrono::microseconds FRAME_DURATION( 16667 ); //defining a frame to be 0.016667 seconds

