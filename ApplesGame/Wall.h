#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
namespace ApplesGame
{
	struct Wall
	{
		Position2D position;
		sf::Sprite sprite;
	};
	struct Game;
	void InitWall(Wall& wall, const Game& game);
	void DrawWall(Wall& wall, sf::RenderWindow& window);
}