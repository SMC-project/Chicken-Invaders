#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include"Wave.h"
#include"ScrollBackground.h"
#include "Player.h"
#include "Chicken.h"
#include "Asteroid.h"
#include "Present.h"
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
	//Class member decalration
	Wave Wave1;
	Chicken chicken[5][8];
	Chicken explode;
	Present present(500,500);

	Asteroid asteroid;

	//Texture declaration
	Texture enemy,explode_texture,asteroid_texture,presentTexture;


	



	
	//The plece where we are setting Sprites
	Wave1.setSprite(enemy, chicken);
	Wave1.setSprite_explosion(explode_texture,explode);
	Wave1.setSprite_asteroid(asteroid_texture, asteroid);

	present.setSpritePresent(presentTexture, present);
	Player player("Sprites/ship.png", Vector2<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));
	player.LoadLiveSprites("Sprites/Extras/heart.png");
	player.SetUpScore("Fonts/Montserrat-Regular.ttf");
	Wave1.fisrtWavePosition(chicken,WINDOW_WIDTH,WINDOW_HEIGHT);
	present.setPosition(present);
	//present.movePresent(present);
	ScrollBackground gameBackground("Sprites/Extras/gbackground.png");

	//Game widow
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
				if (eventHandler.key.code == Keyboard::Right)
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
		

		#pragma region DrawEverything
		gameBackground.AnimateBackground();
		gameBackground.drawBackground(gameWindow);
		Wave1.drawWave(gameWindow, chicken);
		Wave1.movementFirstWave(chicken,explode);
		
		Wave1.explosion_setPosition(explode, 100, 100);
		Wave1.asteroid_setPosition(asteroid, 100, 200);
		Wave1.draw_explosion(gameWindow, explode);

		Wave1.draw_asteroid(gameWindow, asteroid);


		present.drawPresent(gameWindow, present);
		

		

		player.Animate();
		player.DrawShip(gameWindow);
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);
		
		#pragma endregion

		gameWindow.display();
	}
}



