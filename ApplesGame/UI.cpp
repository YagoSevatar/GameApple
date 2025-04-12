#include "UI.h"
#include "Constants.h"

namespace ApplesGame
{
    void InitUI(UIState& uiState, const sf::Font& font)
    {
        uiState.scoreText.setFont(font);
        uiState.scoreText.setCharacterSize(24);
        uiState.scoreText.setFillColor(sf::Color::White);
        uiState.scoreText.setPosition(10.f, 10.f);
        uiState.scoreText.setString("Apples eaten: 0");

        uiState.controlsText.setFont(font);
        uiState.controlsText.setCharacterSize(20);
        uiState.controlsText.setFillColor(sf::Color::White);
        uiState.controlsText.setString("Use arrow keys to move,ESC for Exit");

        sf::FloatRect textBounds = uiState.controlsText.getLocalBounds();
        uiState.controlsText.setPosition(SCREEN_WIDTH - textBounds.width - 10.f, 10.f);

        uiState.gameOverText.setFont(font);
        uiState.gameOverText.setCharacterSize(48);
        uiState.gameOverText.setFillColor(sf::Color::Red);
        uiState.gameOverText.setString("GAME OVER");

        sf::FloatRect textRect = uiState.gameOverText.getLocalBounds();
        uiState.gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        uiState.gameOverText.setPosition(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

        uiState.gameOverText.setFillColor(sf::Color::Transparent);
    }

    void DrawUI(UIState& uiState, sf::RenderWindow& window)
    {
        window.draw(uiState.scoreText);
        window.draw(uiState.controlsText);
        window.draw(uiState.gameOverText);
    }

    void UpdateUIScore(UIState& uiState, short score)
    {
        uiState.scoreText.setString("Apples eaten: " + std::to_string(score));
    }

    void ShowGameOverText(UIState& uiState, bool show)
    {
        uiState.gameOverText.setFillColor(show ? sf::Color::Red : sf::Color::Transparent);
    }
}