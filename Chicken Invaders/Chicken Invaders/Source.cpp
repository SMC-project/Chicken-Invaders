#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include"Wave.h"

#include "Player.h"
#include "Chicken.h"
using namespace sf;


void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);

int main()
{
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	RenderWindow gameWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chicken Invaders DX", Style::Fullscreen);
	gameWindow.setFramerateLimit(30);

	GameLoop(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

	return 0;
}


void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
	Wave Wave1;
	Chicken chicken[5][8];

	Texture texture_background, enemy;
	texture_background.loadFromFile("Sprites/Extras/background.png");
	//enemy.loadFromFile("Sprites/Enemy/Normal Chicken/Idle/chicken_animation.png");
	Sprite sprite_background(texture_background);
	sprite_background.setPosition(0, 0);
	sprite_background.setScale(1, 1);

	Wave1.setSprite(enemy, chicken);
	
	Player player("Sprites/Ship/ship.png", Vector2<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));
	player.LoadLiveSprites("Sprites/Extras/heart.png");
	player.SetUpScore("Fonts/Montserrat-Regular.ttf");

	while (gameWindow.isOpen())
	{
		#pragma region Input

		Event eventHandler;
		while (gameWindow.pollEvent(eventHandler))
		{
			if (eventHandler.type == Event::KeyPressed)
			{
				if (eventHandler.key.code == Keyboard::Left)
					player.SetMovement(false, 1);
				if (eventHandler.key.code == Keyboard::Right)
					player.SetMovement(true, 1);
			}
			if (eventHandler.type == Event::KeyReleased)
			{
				if (eventHandler.key.code == Keyboard::Escape)
					gameWindow.close();
				if (eventHandler.key.code == Keyboard::Left)
					player.SetMovement(false, 0);
				if(eventHandler.key.code == Keyboard::Right)
					player.SetMovement(true, 0);
			}
		}

		#pragma endregion

		#pragma region Movement

		player.MoveShip(WINDOW_WIDTH);

		#pragma endregion

		#pragma region Collisions
		#pragma endregion

		gameWindow.clear();
		Wave1.fisrtWavePosition(chicken);

		#pragma region DrawEverything

		gameWindow.draw(sprite_background);
		Wave1.drawWave(gameWindow, chicken);

		player.DrawShip(gameWindow);
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);

		#pragma endregion

		gameWindow.display();
	}
}


