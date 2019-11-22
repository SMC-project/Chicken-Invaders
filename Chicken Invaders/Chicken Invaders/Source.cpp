#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>

#include"Wave.h"
#include"ScrollBackground.h"
#include "Player.h"
#include "Chicken.h"
#include "Asteroid.h"
#include"Explosion.h"
#include "Present.h"
#include "Egg.h"
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
	Explosion explode;
	Asteroid asteroid;
	Present present;
	Texture enemy,explode_texture,asteroid_texture,presentTexture;
	//enemy.loadFromFile("Sprites/Enemy/Normal Chicken/Idle/chicken_animation.png");

	Chicken explode;
	Present present(500,500);

	Asteroid asteroid;

	//Texture declaration
	Texture enemy,explode_texture,asteroid_texture,presentTexture;
	
	//The plece where we are setting Sprites
	Wave1.setSprite(enemy, chicken);

	explode.setSprite_explosion(explode_texture,explode);
	

	asteroid.setSprite_asteroid(asteroid_texture, asteroid);

	present.setSpritePresent(presentTexture, present);

	
	
	
	Player player("Sprites/Ship/ship.png", Vector2<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));
	Wave1.setSprite_explosion(explode_texture,explode);
	Wave1.setSprite_asteroid(asteroid_texture, asteroid);

	present.setSpritePresent(presentTexture, present);
	Player player("Sprites/ship.png", Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));
	player.LoadLiveSprites("Sprites/Extras/heart.png");
	player.SetUpScore("Fonts/Montserrat-Regular.ttf");
	Wave1.fisrtWavePosition(chicken,WINDOW_WIDTH,WINDOW_HEIGHT);
	present.setPosition(present);
	//present.movePresent(present);
	ScrollBackground gameBackground("Sprites/Extras/gbackground.png");

	//Vector that will hold all the eggs on the screen, when the exit the screen or collide we take them out.
	std::vector<Egg> eggs;

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
				//This is only for testing purposes, delete it after implementing chickens to shoot eggs
				if (eventHandler.key.code == Keyboard::R)
				{
					for (int index = 0; index < 5; index++)
					{
						eggs.push_back(std::move(Egg("Sprites/Weapons/egg.png", sf::Vector2f(320 * (index + 1), 50 * (index + 1)))));
					}
				}
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
		//Move each egg from the eggs vector
		for (int index = 0; index < eggs.size(); index++)
			if (eggs[index].FallDown(WINDOW_HEIGHT))
				eggs.erase(eggs.begin() + index);


		#pragma endregion

		#pragma region Collisions

		//Check if any of the eggs collides with the ship
		for(int index = 0; index < eggs.size(); index++)
			if (player.CheckCollision(eggs[index].GetPosition(), eggs[index].GetSize()))
			{
				//If so erase the egg and kill the player
				eggs.erase(eggs.begin() + index);
				player.Die();
			}

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

		Wave1.movementFirstWave(chicken,explode);
		Wave1.explosion_setPosition(explode, 100, 100);
		Wave1.asteroid_setPosition(asteroid, 100, 200);
		Wave1.draw_explosion(gameWindow, explode);
		Wave1.draw_asteroid(gameWindow, asteroid);

		present.drawPresent(gameWindow, present);


		//Draw all the eggs
		for (int index = 0; index < eggs.size(); index++)
			eggs[index].DrawEgg(gameWindow);

		player.Animate();
		player.DrawShip(gameWindow);
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);
		
		#pragma endregion

		gameWindow.display();
	}
}
