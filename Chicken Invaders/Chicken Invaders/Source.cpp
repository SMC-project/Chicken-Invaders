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
#include"TitleScreen.h"
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
	int wave_number = 0;
	Wave Wave1;
	Wave Wave3;
	Chicken chicken[5][8];
	Explosion explode;
	
	Present present;
	bool selected = true;
	bool start_game = false;
#pragma region music
	//bg music
	Music background_music;
	background_music.openFromFile("Music/c.ogg");
	background_music.play();

#pragma endregion

#pragma region User Interface
	Sprite leaderboard_button, leaderboard_hover, exit_button, exit_hover, side_texture, main_background, play_button,tip;
	Texture t1, t2, t3, t4, t5, t6, t7,t8;
	TitleScreen titleScreen;
#pragma endregion


	
	//Texture declaration
	Texture enemy,explode_texture,asteroid_texture,presentTexture;
	
	//The plece where we are setting Sprites
	
		titleScreen.IntroMain_SetTextures(t1, t2, t3, t4, t5, t6, t7,t8, titleScreen,WINDOW_WIDTH,WINDOW_HEIGHT);
	
		Wave1.setSprite(enemy, chicken);
		Wave1.fisrtWavePosition(chicken,WINDOW_WIDTH,WINDOW_HEIGHT);
		explode.setSprite_explosion(explode_texture, explode);
		present.setSpritePresent(presentTexture, present);

		

	
	
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
#pragma region Asteroids init
	//Vector that will contain all the asteroids
	std::vector<Asteroid> asteroids;
#pragma region Asteroids init
	float random_number;
	srand(time(NULL));
	random_number = rand() % 900;
	random_number = -random_number;
	float current_x = random_number;

	random_number = rand() % 900;
	random_number = -random_number;
	float current_y = random_number;
	for (int index = 0; index < 15; index++)
	{
		asteroids.push_back(std::move(Asteroid(sf::Vector2f(current_x, current_y))));
	}
#pragma endregion
#pragma endregion

	
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
				
				if (eventHandler.key.code == Keyboard::Left)
					player.SetMovement(false, 0);
				if (eventHandler.key.code == Keyboard::Right)
					player.SetMovement(true, 0);
			}
		}
		//The game starts when you are in title screen and press space
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (start_game == false)
			{
				wave_number = 3;
				start_game = true;
			}
			
		}
		//Escape button closes the game only if you pass the title screen
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			if (start_game)
				gameWindow.close();
		}
		//You can select between leaderboards button and exit button
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			selected = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			selected = false;
		}
		

		#pragma endregion

		#pragma region Movement of the egg

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
		
		if (wave_number == 0)
		{
			titleScreen.IntroMain_Display(gameWindow, titleScreen);
		}
		 if (wave_number == 1)
		{
		    gameBackground.AnimateBackground();
			gameBackground.drawBackground(gameWindow);
			Wave1.drawWave(gameWindow, chicken);
			Wave1.movementFirstWave(chicken);

			explode.explosion_setPosition(explode, 100, 100);
			explode.draw_explosion(gameWindow, explode);

			present.drawPresent(gameWindow, present);
			present.setPositionPresent(present, 100, 100);
			present.drawPresent(gameWindow, present);

			player.Animate();
			player.DrawShip(gameWindow);
			player.DrawLives(gameWindow);
			player.DrawScore(gameWindow);

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
		else if (wave_number == 3)
		{	
#pragma region Background
			 gameBackground.AnimateBackground();
			 gameBackground.drawBackground(gameWindow);
#pragma endregion
#pragma region Player
			player.Animate();
			player.DrawShip(gameWindow);
			player.DrawLives(gameWindow);
			player.DrawScore(gameWindow);

#pragma endregion

#pragma region Asteroids movement
			for (int index = 0; index < asteroids.size(); index++)
				if (asteroids[index].Falldown(WINDOW_HEIGHT))
					asteroids.erase(asteroids.begin() + index);
#pragma endregion
#pragma region Asteroid collision
			for (int index = 0; index < asteroids.size(); index++)
				if (player.CheckCollision(asteroids[index].GetPosition(), asteroids[index].GetSize()))
				{
					//If so erase the asteroid and kill the player
					asteroids.erase(asteroids.begin() + index);
					player.Die();
					Contor = 0;
				}
#pragma endregion

			//Draw all asteroids
			for (int index = 0; index < asteroids.size(); index++)
				asteroids[index].draw_asteroid(gameWindow);
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

		for (int i = 0; i < GameBullets.size(); i++)
		{ 
			GameBullets[i].Shot(gameWindow);
		
			if (GameBullets[i].CheckIfBulletIsOnTheScreen(WINDOW_HEIGHT) == true)
				GameBullets.erase(GameBullets.begin() + i);
		}
		//Draw all the eggs
		for (int index = 0; index < eggs.size(); index++)
			eggs[index].DrawEgg(gameWindow);
		

		if (selected)
		{
			if (!start_game)
				titleScreen.menu_Select(gameWindow, titleScreen, selected);

		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				gameWindow.close();
			if(!start_game)
				titleScreen.menu_Select(gameWindow, titleScreen, selected);

		}
		
		#pragma endregion

		gameWindow.display();
	}
}
