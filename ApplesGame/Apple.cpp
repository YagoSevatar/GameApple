#include "Apple.h"
#include "constants.h"
#include "Game.h"

void ApplesGame::InitApple(Apple& apple, const Game& game)
{
	apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
	apple.sprite.setTexture(game.appleTexture);
	SetSpriteSize(apple.sprite, PLAYER_SIZE, PLAYER_SIZE);
	SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
}

void ApplesGame::DrawApple(Apple& apple, sf::RenderWindow& window)
{
	apple.sprite.setPosition(apple.position.x, apple.position.y);
	window.draw(apple.sprite);
}
