#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
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
#include"Bullet.h"
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
	Wave wave_number;
	Wave Wave1;
	Wave Wave3;
	Chicken chicken[5][8];
	Explosion explode;
	Asteroid asteroid[5][5];
	Present present;

	wave_number.wave_number = 1;

	//bg music
	Music background_music;
	background_music.openFromFile("Music/c.ogg");
	background_music.play();


	
	//Texture declaration
	Texture enemy,explode_texture,asteroid_texture,presentTexture;
	
	//The plece where we are setting Sprites
	if (wave_number.wave_number == 1)
	{
		Wave1.setSprite(enemy, chicken);
		Wave1.fisrtWavePosition(chicken,WINDOW_WIDTH,WINDOW_HEIGHT);

		explode.setSprite_explosion(explode_texture, explode);

		present.setSpritePresent(presentTexture, present);

	}
	else if (wave_number.wave_number == 3)
	{
	}

		Wave3.setSprite_asteroid1(asteroid_texture,asteroid);
		Wave3.thirdWave_Position(asteroid);

	
	
	
	
	//Player player("Sprites/Ship/ship.png", Vector2<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));
	Player player("Sprites/ship.png", Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));
	player.LoadLiveSprites("Sprites/Extras/heart.png");
	player.SetUpScore("Fonts/Montserrat-Regular.ttf");
	Wave1.fisrtWavePosition(chicken,WINDOW_WIDTH,WINDOW_HEIGHT);
	

	ScrollBackground gameBackground("Sprites/Extras/gbackground.png");
	//Gloantele din joc
	std::vector<Bullet> GameBullets;
	//Contor folosit pentru teste
	int Contor = 0;
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
				//Funtie folosita pentru teste
				if (Keyboard::isKeyPressed(Keyboard::Num1))
				{
					Contor++;
					if (Contor > 6)
						Contor = 7;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					Bullet x(player.GetPosition().x, player.GetPosition().y);
					for (int i = 0; i < Contor; i++)
					{
						x.Present_Collected();
					}
					GameBullets.push_back(std::move(x));
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
				Contor = 0;
			}

		#pragma endregion

		gameWindow.clear();
		

		#pragma region DrawEverything
		gameBackground.AnimateBackground();
		gameBackground.drawBackground(gameWindow);
		if (wave_number.wave_number == 1)
		{
			Wave1.drawWave(gameWindow, chicken);
			Wave1.movementFirstWave(chicken,wave_number);

			explode.explosion_setPosition(explode, 100, 100);
			explode.draw_explosion(gameWindow, explode);

			present.drawPresent(gameWindow, present);
			present.setPositionPresent(present, 100, 100);
			present.drawPresent(gameWindow, present);

		}
		else if (wave_number.wave_number == 3)
		{	
			Wave3.drawWave_asteroid(gameWindow, asteroid);
			Wave3.thirdWave_Movement(asteroid);
		}

		for (int i = 0; i < GameBullets.size(); i++)
		{ 
			GameBullets[i].Shot(gameWindow);
		
			if (GameBullets[i].CheckIfBulletIsOnTheScreen(WINDOW_HEIGHT) == true)
				GameBullets.erase(GameBullets.begin() + i);
		}
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
