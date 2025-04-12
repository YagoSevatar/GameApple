#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
    struct UIState
    {
        sf::Text scoreText;
        sf::Text controlsText;
        sf::Text gameOverText;
    };

    void InitUI(UIState& uiState, const sf::Font& font);
    void DrawUI(UIState& uiState, sf::RenderWindow& window);
    void UpdateUIScore(UIState& uiState, short score);
    void ShowGameOverText(UIState& uiState, bool show);
}
