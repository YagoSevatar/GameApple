#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
    struct Record
    {
        std::string name;
        int score;
    };
    struct UIState
    {
        sf::Text scoreText;
        sf::Text controlsText;
        sf::Text gameOverText;
        sf::Text leaderboardText;
        sf::Text RestartHintText;
        std::vector<Record> highScores;
        bool isHighScoresPrepared = false;
    };

    void InitUI(UIState& uiState, const sf::Font& font);
    void DrawUI(UIState& uiState, sf::RenderWindow& window);
    void UpdateUIScore(UIState& uiState, short score);
    void ShowGameOverText(UIState& uiState, bool show);
    void HighScores(UIState& uiState, int score);
    
}
