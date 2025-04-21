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

        uiState.leaderboardText.setFont(font);
        uiState.leaderboardText.setCharacterSize(20);
        uiState.leaderboardText.setFillColor(sf::Color::Yellow);

        sf::FloatRect textScore = uiState.leaderboardText.getLocalBounds();
        uiState.leaderboardText.setOrigin(textScore.left + textScore.width / 10.0f,
            textScore.top + textScore.height / 10.0f);
        uiState.leaderboardText.setPosition(SCREEN_WIDTH / 2.4f, SCREEN_HEIGHT / 1.7f);

        uiState.RestartHintText.setFont(font);
        uiState.RestartHintText.setCharacterSize(20);
        uiState.RestartHintText.setFillColor(sf::Color::White);
        uiState.RestartHintText.setString("Press R for restart or Esc for Exit");
        sf::FloatRect textHint = uiState.leaderboardText.getLocalBounds();
        uiState.RestartHintText.setOrigin(textHint.left + textHint.width / 2.0f,
            textHint.top + textHint.height / 2.0f);
        uiState.RestartHintText.setPosition(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT /3.0f);
        uiState.RestartHintText.setFillColor(sf::Color::Transparent);

    }
    void HighScores(UIState& uiState, int score)
    {
        if (uiState.isHighScoresPrepared) return;

        // Очищаем предыдущие рекорды
        uiState.highScores.clear();

        // Добавляем выдуманные результаты (фиксированные значения)
        uiState.highScores.push_back({ "Alice", 35 });
        uiState.highScores.push_back({ "Bob", 15 });
        uiState.highScores.push_back({ "Lee", 6 });
        uiState.highScores.push_back({ "Noob", 111 });
        // Добавляем текущий результат игрока
        uiState.highScores.push_back({ "Player", score });

        // Сортируем по убыванию очков
        std::sort(uiState.highScores.begin(), uiState.highScores.end(),
            [](const Record& l, const Record& r)
            {
                if (l.score != r.score) {
                    return l.score > r.score;
                }
                return l.name < r.name;
            });

        // Формируем текст для отображения (максимум 5 записей)
        std::string highScoreString = "High Scores:\n";
        for (size_t i = 0; i < std::min(uiState.highScores.size(), size_t(5)); ++i)
        {
            highScoreString += std::to_string(i + 1) + ". " +
                uiState.highScores[i].name + ": " +
                std::to_string(uiState.highScores[i].score) + "\n";
        }

        uiState.leaderboardText.setString(highScoreString);
        uiState.isHighScoresPrepared = true;
        
    }
    void DrawUI(UIState& uiState, sf::RenderWindow& window)
    {
        window.draw(uiState.scoreText);
        window.draw(uiState.controlsText);
        window.draw(uiState.gameOverText);
        window.draw(uiState.leaderboardText);
        window.draw(uiState.RestartHintText);
    }

    void UpdateUIScore(UIState& uiState, short score)
    {
        uiState.scoreText.setString("Apples eaten: " + std::to_string(score));
    }

    void ShowGameOverText(UIState& uiState, bool show)
    {
        uiState.gameOverText.setFillColor(show ? sf::Color::Red : sf::Color::Transparent);
        uiState.RestartHintText.setFillColor(show ? sf::Color::White : sf::Color::Transparent);
        uiState.leaderboardText.setFillColor(show ? sf::Color::White : sf::Color::Transparent);
    }
    
}