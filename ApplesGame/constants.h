#pragma once
#include <string>
namespace ApplesGame
{
    const std::string RESOURCES_PATH = "Resources/";
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const float INITIAL_SPEED = 100.f;
    const float PLAYER_SIZE = 20.f;
    const float ACCELERATION = 10.f;
    const int MAX_APPLES = 30; 
    const float APPLE_SIZE = 20.f;
    const float PAUSE_LENGTH = 2.f;
    const int NUM_WALLS = 10;
    const float WALL_SIZE = 20.f;
    const float PAUSE_TIME = 2.0f;


    enum GameMode
    {
        INFINITE_APPLES = 1,     
        WITH_ACCELERATION = 2,  
    };
}