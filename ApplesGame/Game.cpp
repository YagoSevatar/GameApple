#include "Game.h"
#include <cassert>
namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        InitPlayer(game.player, game);

        // Освобождаем старый массив в начале цикла
        game.apple.clear();
        // Количество яблок зависит от режима
        game.numApplesOnScreen = (game.gameMode & INFINITE_APPLES) ? MAX_APPLES : MAX_APPLES / 2;

        // Выделяем память под массив
        game.apple.resize (game.numApplesOnScreen);

        for (short i = 0; i < game.numApplesOnScreen; ++i)
        {
            InitApple(game.apple[i], game);
        }

        for (short i = 0; i < NUM_WALLS; ++i)
        {
            InitWall(game.wall[i], game);
        }

        game.numEatenApples = 0;
        game.isGameFinished = false;
        game.timeSinceGameFinish = 0;
        game.player.speed = INITIAL_SPEED;
        UpdateUIScore(game.uiState, game.numEatenApples);
        game.uiState.isHighScoresPrepared = false;
    }

    void InitGame(Game& game)
    {
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
        assert(game.wallTexture.loadFromFile(RESOURCES_PATH + "\\wall.png"));
        assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
        assert(game.EatSound.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
        assert(game.DeathSound.loadFromFile(RESOURCES_PATH + "\\Death.wav"));

        game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        game.background.setFillColor(sf::Color::Black);
        game.background.setPosition(0.f, 0.f);
        game.eatSoundPlayer.setBuffer(game.EatSound);
        game.deathSoundPlayer.setBuffer(game.DeathSound);
        InitUI(game.uiState, game.font);

        game.gameMode = 0;
        RestartGame(game);
    }

    void UpdateGame(Game& game, float deltaTime)
    {
        if (!game.isGameFinished)
        {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                game.player.direction = PlayerDirection::Right;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                game.player.direction = PlayerDirection::Up;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                game.player.direction = PlayerDirection::Left;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                game.player.direction = PlayerDirection::Down;
            }

            switch (game.player.direction)
            {
            case PlayerDirection::Right:
                game.player.position.x += game.player.speed * deltaTime;
                break;
            case PlayerDirection::Up:
                game.player.position.y -= game.player.speed * deltaTime;
                break;
            case PlayerDirection::Left:
                game.player.position.x -= game.player.speed * deltaTime;
                break;
            case PlayerDirection::Down:
                game.player.position.y += game.player.speed * deltaTime;
                break;
            }

            for (short i = 0; i < game.numApplesOnScreen; ++i)
            {
                if (IsCirclesCollide(game.player.position, PLAYER_SIZE / 2.f,
                    game.apple[i].position, APPLE_SIZE / 2.f))
                {
                    if (game.gameMode & INFINITE_APPLES)
                    {
                        game.apple[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                    else 
                    {
                        std::swap(game.apple[i], game.apple[game.numApplesOnScreen - 1]);
                        game.numApplesOnScreen--;
                    }

                    game.numEatenApples++;
                    game.eatSoundPlayer.play();

                    if (game.gameMode & WITH_ACCELERATION)
                    {
                        game.player.speed += ACCELERATION;
                    }

                    UpdateUIScore(game.uiState, game.numEatenApples);

                    if (!(game.gameMode & INFINITE_APPLES) && game.numApplesOnScreen == 0)
                    {
                        game.isGameFinished = true;
                        game.timeSinceGameFinish = 0.f;
                        ShowGameOverText(game.uiState, true);
                        HighScores(game.uiState, game.numEatenApples);
                    }

                    break;
                }
            }

            for (short i = 0; i < NUM_WALLS; ++i)
            {
                if (IsRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE },
                    game.wall[i].position, { WALL_SIZE, WALL_SIZE }))
                {
                    game.isGameFinished = true;
                    game.timeSinceGameFinish = 0.f;
                    game.deathSoundPlayer.play();
                    ShowGameOverText(game.uiState, true);
                    HighScores(game.uiState, game.numEatenApples);
                }
            }

            if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f ||
                game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
                game.player.position.y - PLAYER_SIZE / 2.f < 0.f ||
                game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
            {
                game.isGameFinished = true;
                game.timeSinceGameFinish = 0.f;
                game.deathSoundPlayer.play();
                ShowGameOverText(game.uiState, true);
                HighScores(game.uiState, game.numEatenApples);
            }
        }
        
        else
        {
            game.timeSinceGameFinish += deltaTime;

            // Обработка ввода после завершения игры
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                game.background.setFillColor(sf::Color::Black);
                RestartGame(game);
                ShowGameOverText(game.uiState, false);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                // Выход из игры будет обработан в главном цикле
            }

            // Автоматический рестарт после паузы, только если не нажаты клавиши
            if (game.timeSinceGameFinish >= PAUSE_LENGTH &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                game.background.setFillColor(sf::Color::Black);
                RestartGame(game);
                ShowGameOverText(game.uiState, false);
            }
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.background);
        DrawPlayer(game.player, window);

        for (short i = 0; i < game.numApplesOnScreen; ++i)
        {
            DrawApple(game.apple[i], window);
        }

        for (short i = 0; i < NUM_WALLS; ++i)
        {
            DrawWall(game.wall[i], window);
        }

        DrawUI(game.uiState, window);
    }

    void DeinializeGame(Game& game)
    {
        // освобождения памяти
       game.apple.clear();
    }
};