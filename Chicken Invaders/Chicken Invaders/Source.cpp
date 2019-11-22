#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include"Wave.h"
#include"ScrollBackground.h"
#include "Player.h"
#include "Chicken.h"
#include "Asteroid.h"
#include"Present.h"
#include"Explosion.h"
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
	Explosion explode;
	Asteroid asteroid;
	Present present;
	Texture enemy,explode_texture,asteroid_texture,presentTexture;
	//enemy.loadFromFile("Sprites/Enemy/Normal Chicken/Idle/chicken_animation.png");


	

	
	//The plece where we are setiing Sprites
	Wave1.setSprite(enemy, chicken);
	explode.setSprite_explosion(explode_texture,explode);
	

	asteroid.setSprite_asteroid(asteroid_texture, asteroid);

	present.setSpritePresent(presentTexture, present);

	
	
	
	Player player("Sprites/Ship/ship.png", Vector2<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));
	player.LoadLiveSprites("Sprites/Extras/heart.png");
	player.SetUpScore("Fonts/Montserrat-Regular.ttf");
	Wave1.fisrtWavePosition(chicken,WINDOW_WIDTH,WINDOW_HEIGHT);
	ScrollBackground gameBackground("Sprites/Extras/gbackground.png");

	
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
		

		#pragma region DrawEverything
		gameBackground.AnimateBackground();
		gameBackground.drawBackground(gameWindow);
		Wave1.drawWave(gameWindow, chicken);
		Wave1.movementFirstWave(chicken);
		
		explode.explosion_setPosition(explode, 100, 100);
		explode.draw_explosion(gameWindow, explode);

		asteroid.asteroid_setPosition(asteroid, 100, 200);
		asteroid.draw_asteroid(gameWindow, asteroid);

		present.drawPresent(gameWindow, present);
		present.setPositionPresent(present, 100, 100);


		player.DrawShip(gameWindow);
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);
		
		#pragma endregion

		gameWindow.display();
	}
}



