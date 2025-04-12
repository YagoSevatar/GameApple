#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Wall.h"
#include "UI.h"

namespace ApplesGame
{
    struct Game
    {
        Player player;
        Apple* apple = nullptr;;//добавлен динамический массив
        Wall wall[NUM_WALLS];

        short numEatenApples = 0;
        short numApplesOnScreen = 0; 
        UIState uiState;
        bool isGameFinished = false;
        float timeSinceGameFinish = 0.f;
        uint32_t gameMode = 0; //исплавлен short на uint32_t

        sf::RectangleShape background;
        sf::Font font;
        sf::SoundBuffer EatSound;
        sf::SoundBuffer DeathSound;
        sf::Sound eatSoundPlayer;
        sf::Sound deathSoundPlayer;
        sf::Texture appleTexture;
        sf::Texture wallTexture;
        sf::Texture playerTexture;
    };

    void RestartGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, float deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinializeGame(Game& game);
}