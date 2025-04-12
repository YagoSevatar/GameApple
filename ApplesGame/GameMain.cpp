#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"
#include "Game.h"

int main()
{
    using namespace ApplesGame;
    short seed = (short)time(nullptr);
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

    Game game;
    InitGame(game);

    bool modeSelected = false;
    sf::Text modeText;
    modeText.setFont(game.font);
    modeText.setCharacterSize(24);
    modeText.setFillColor(sf::Color::White);
    modeText.setString(
        "Select game mode:\n"
        "1. Finite apples, no acceleration\n"
        "2. Finite apples with acceleration\n"
        "3. Infinite apples, no acceleration\n"
        "4. Infinite apples with acceleration\n"
        "Press corresponding number key"
    );
    modeText.setPosition(50.f, 50.f);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            if (!modeSelected && event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Num1:
                    game.gameMode = 0; 
                    modeSelected = true;
                    break;
                case sf::Keyboard::Num2:
                    game.gameMode = WITH_ACCELERATION; 
                    modeSelected = true;
                    break;
                case sf::Keyboard::Num3:
                    game.gameMode = INFINITE_APPLES; 
                    modeSelected = true;
                    break;
                case sf::Keyboard::Num4:
                    game.gameMode = INFINITE_APPLES | WITH_ACCELERATION; 
                    modeSelected = true;
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                default:
                    break;
                }

                if (modeSelected)
                {
                    RestartGame(game);
                }
            }
            else if (modeSelected && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                break;
            }
        }

        window.clear();

        if (modeSelected)
        {
            UpdateGame(game, deltaTime);
            DrawGame(game, window);
        }
        else
        {
            window.draw(modeText);
        }

        window.display();
    }

    DeinializeGame(game);

    return 0;
}