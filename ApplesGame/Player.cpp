#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}
    void UpdatePlayerRotation(Player& player)
    {
        switch (player.direction)
        {
        case PlayerDirection::Right:
            player.sprite.setRotation(0.f); 
            break;
        case PlayerDirection::Down:
            player.sprite.setRotation(90.f);
            break;
        case PlayerDirection::Left:
            player.sprite.setRotation(180.f);
            break;
        case PlayerDirection::Up:
            player.sprite.setRotation(270.f); 
            break;
        }
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
    
        UpdatePlayerRotation(player);

  
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);
    }
}
