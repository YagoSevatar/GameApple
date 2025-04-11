#include "Wall.h"
#include "constants.h"
#include "Game.h"

namespace ApplesGame
{
	void InitWall(Wall& wall, const Game& game)
	{
		wall.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		wall.sprite.setTexture(game.wallTexture);
		SetSpriteSize(wall.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(wall.sprite, 0.5f, 0.5f);
	}
	void DrawWall(Wall& wall, sf::RenderWindow& window)
	{
		wall.sprite.setPosition(wall.position.x, wall.position.y);
		window.draw(wall.sprite);
	}
}
