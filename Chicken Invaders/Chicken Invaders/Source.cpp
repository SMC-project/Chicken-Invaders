#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "ResourceLoader.h"
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
#include"Missile.h"
#include "Meat.h"
using namespace sf;

#pragma region Methods

void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& selected, Player& player, ResourceLoader& resourceLoader, std::vector<Egg>& eggs, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Asteroid>& asteroids, std::vector<Meat>& meat);
void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, Present& present, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, bool& start_wave3);
void CheckCollisions(ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions);
void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Present& present, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat);
bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Present& present, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens);
bool Init_asteroids(ResourceLoader& resourceLoader, std::vector<Asteroid>& asteroids);
#pragma endregion

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
#pragma region Variables

	Clock clock;
	Time lastFrameTime;
	Time deltaTime;
	ResourceLoader resourceLoader;
	sf::Text loadingText;

	Wave Wave1;
	Wave Wave3;
	int wave_number = 0;

	Present present;

	bool selected = true;
	bool start_game = false;
	bool start_wave3 = false;
	TitleScreen titleScreen;

	Player player;
	ScrollBackground gameBackground;
	std::vector<Bullet> GameBullets;	//Gloantele din joc
	int Contor = 0;						//Contor folosit pentru teste
	//Vector that will hold all the eggs on the screen, when the exit the screen or collide we take them out.
	std::vector<Egg> eggs;
	//Vector that will contain all the asteroids
	std::vector<Asteroid> asteroids;
	//Vector of chickens
	std::vector<Chicken> chickens;
	std::vector<Explosion> explosions;

	std::vector<Meat> meat;

	std::cout << "meat: " << meat.size();

#pragma endregion

	if (Init(WINDOW_WIDTH, WINDOW_HEIGHT, gameWindow, clock, resourceLoader, loadingText, titleScreen, gameBackground, player, present, asteroids, chickens) == false)
		return;

	lastFrameTime = clock.getElapsedTime();

	//Game widow
	while (gameWindow.isOpen())
	{
		deltaTime = clock.getElapsedTime() - lastFrameTime;
		lastFrameTime = clock.getElapsedTime();

		CheckInput(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, start_game, selected, player, resourceLoader, eggs, Contor, GameBullets, asteroids, meat);

		Movement(WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, resourceLoader, gameBackground, player, eggs, chickens, present, asteroids,GameBullets, start_wave3);
		CheckCollisions(resourceLoader, player, Contor, eggs, asteroids, GameBullets, explosions);

		DrawEverything(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, resourceLoader, titleScreen, gameBackground, player, present, chickens, asteroids, GameBullets, eggs, selected, start_game, deltaTime, explosions, meat);
	}
}

bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Present& present, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens)
{
	Time time = clock.getElapsedTime();
	std::cout << "Start: " << time.asSeconds() << "\n";

	if (resourceLoader.Init1() == false)
		return false;

	loadingText.setFont(resourceLoader.GetFont());
	loadingText.setString("Loading...");

	float xLoadingPos = WINDOW_WIDTH - loadingText.getLocalBounds().width - 50;
	float yLoadingPos = WINDOW_HEIGHT - loadingText.getLocalBounds().height - 50;

	loadingText.setPosition(xLoadingPos, yLoadingPos);

	gameWindow.clear();
	gameWindow.draw(loadingText);
	gameWindow.display();

	if (resourceLoader.Init2() == false)
		return false;

	time = clock.getElapsedTime();
	std::cout << "Finish loading resources: " << time.asSeconds() << "\n";

	player.Init(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8), resourceLoader.GetTexture(ResourceLoader::TextureType::Ship));
	gameBackground.Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Background));

	resourceLoader.GetMusic().play();

	titleScreen.IntroMain_SetTextures(WINDOW_WIDTH, WINDOW_HEIGHT, resourceLoader);

	present.setSpritePresent(resourceLoader.GetTexture(ResourceLoader::TextureType::Gift));

	player.LoadLiveSprites(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_heart));
	player.SetUpScore(resourceLoader.GetFont());

	float random_number;
	srand(std::time(NULL));

	for (int index = 0; index < 15; index++)
	{
		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_x = random_number;

		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_y = random_number;

		asteroids.push_back(std::move(Asteroid(sf::Vector2f(current_x, current_y), resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid))));
	}

	for (int index = 0; index < 40; index++)
	{
		chickens.push_back(std::move(Chicken(sf::Vector2f(140 * index + WINDOW_WIDTH / 4, 120 * index + WINDOW_HEIGHT / 9), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}

	gameWindow.clear();
	time = clock.getElapsedTime();
	std::cout << "Starting game: " << time.asSeconds() << "\n";

	return true;
}

bool Init_asteroids(ResourceLoader& resourceLoader, std::vector<Asteroid>& asteroids)
{
	float random_number;
	srand(std::time(NULL));
	for (int index = 0; index < 15; index++)
	{
		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_x = random_number;

		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_y = random_number;

		asteroids.push_back(std::move(Asteroid(sf::Vector2f(current_x, current_y), resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid))));
	}
	return true;
}
void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& selected, Player& player, ResourceLoader& resourceLoader, std::vector<Egg>& eggs, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Asteroid>& asteroids, std::vector<Meat>& meat)
{
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
				int xRand = rand() % WINDOW_WIDTH;
				int yRand = rand() % (WINDOW_HEIGHT / 3);
				Egg clone(sf::Vector2f(xRand, yRand), resourceLoader.GetTexture(ResourceLoader::TextureType::Egg));
				eggs.push_back(std::move(clone));
			}
			if (eventHandler.key.code == Keyboard::E)
			{
				int xRand = rand() % WINDOW_WIDTH;
				int yRand = rand() % (WINDOW_HEIGHT / 3);
				Meat meatClone(sf::Vector2f(xRand, yRand), resourceLoader.GetTexture(ResourceLoader::TextureType::Meat));
				meat.push_back(std::move(meatClone));
			}
			//This is only for testing purposes, delete it after implementing wave transition
			if (eventHandler.key.code == Keyboard::C)
			{
				if (wave_number == 1)
					wave_number = 3;
				asteroids.clear();
			}
			if (eventHandler.key.code == Keyboard::V)
			{
				if (wave_number == 3)
					wave_number = 1;
				asteroids.clear();
			}
			//The game starts when you are in title screen and press space
			if (eventHandler.key.code == Keyboard::Space)
			{
				if (start_game == false)
				{
					wave_number = 1;
					start_game = true;
				}
			}
			//Escape button closes the game only if you pass the title screen
			if (eventHandler.key.code == Keyboard::Escape)
			{
				if (start_game)
					gameWindow.close();
			}
			//You can select between leaderboards button and exit button
			if (eventHandler.key.code == Keyboard::Up)
			{
				selected = true;
			}
			if (eventHandler.key.code == Keyboard::Down)
			{
				selected = false;
			}
			if (eventHandler.key.code == Keyboard::Num1)
			{
				Contor++;
				if (Contor > 6)
					Contor = 7;
			}
			if (eventHandler.key.code == Keyboard::Enter)
			{
				if (selected == false)
					gameWindow.close();
			}
		}
		if (eventHandler.type == Event::KeyReleased)
		{
			if (eventHandler.key.code == Keyboard::Left)
				player.SetMovement(false, 0);
			if (eventHandler.key.code == Keyboard::Right)
				player.SetMovement(true, 0);
			if (eventHandler.key.code == Keyboard::Space)
			{
				Bullet x(player.GetPosition().x, player.GetPosition().y, resourceLoader.GetTexture(ResourceLoader::TextureType::Bullet));
				for (int i = 0; i < Contor; i++)
				{
					x.Present_Collected();
				}
				GameBullets.push_back(std::move(x));
			}
		} 
	
	}
}

void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, Present& present, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, bool& start_wave3)
{
	gameBackground.AnimateBackground();
	player.MoveShip(WINDOW_WIDTH);
	//Move each egg from the eggs vector
	for (int index = 0; index < eggs.size(); index++)
		if (eggs[index].FallDown(WINDOW_HEIGHT))
			eggs.erase(eggs.begin() + index);
	//BulletMovement
	for (int i = 0; i < GameBullets.size(); i++)
	{
		GameBullets[i].BulletsPosition_Update();
		if (GameBullets[i].CheckIfBulletIsOnTheScreen(WINDOW_HEIGHT) == true)
			GameBullets.erase(GameBullets.begin() + i);
	}
	if (wave_number == 1)
	{
		for (int index = 0; index < chickens.size(); index++)
			chickens[index].chickenMovement(WINDOW_WIDTH);

	}
	if (wave_number == 3)
	{
		if (!start_wave3)
		{
			start_wave3 = true;		
			if (!Init_asteroids(resourceLoader, asteroids))
				return;
		}
		for (int index = 0; index < asteroids.size(); index++)
		{
			if (asteroids[index].Falldown(WINDOW_HEIGHT))
			{
				asteroids.erase(asteroids.begin() + index);
				
			}
			
				
		}
	}
	else
		start_wave3 = false;

	present.fallDownPresent(WINDOW_HEIGHT);
}

void CheckCollisions(ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions)
{
	//Check if any of the eggs collides with the ship
	for (int index = 0; index < eggs.size(); index++)
		if (player.CheckCollision(eggs[index].GetPosition(), eggs[index].GetSize()))
		{
			if (player.IsPlayerDead() == false)
			{
				//If so erase the egg and kill the player
				eggs.erase(eggs.begin() + index);

				explosions.push_back(Explosion());
				explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
				explosions[explosions.size() - 1].explosion_setPosition(player.GetPosition().x, player.GetPosition().y);
				player.Die();
				Contor--;
			}
		}

	for (int index = 0; index < asteroids.size(); index++)
		if (player.CheckCollision(asteroids[index].GetPosition(), asteroids[index].GetSize()))
		{
			if (player.IsPlayerDead() == false)
			{
				//If so erase the asteroid and kill the player
				asteroids.erase(asteroids.begin() + index);

				explosions.push_back(Explosion());
				explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
				explosions[explosions.size() - 1].explosion_setPosition(player.GetPosition().x, player.GetPosition().y);

				player.Die();
				Contor--;
			}
		}
	for(int index=0;index<asteroids.size();index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for(int z=0;z<7;z++)
				if (GameBullets[j].CheckCollision(asteroids[index].GetPosition()+Vector2f(0,130), asteroids[index].GetSize()-Vector2f(0,130), z))  
				{    
					explosions.push_back(Explosion());
					explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
					explosions[explosions.size() - 1].explosion_setPosition(asteroids[index].GetPosition().x-20, asteroids[index].GetPosition().y+130);
					asteroids.erase(asteroids.begin() + index);
					z = 7;
					j = GameBullets.size();
				}
}

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Present& present, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat)
{
	gameWindow.clear();

	if (wave_number == 0)
	{
		titleScreen.IntroMain_Display(gameWindow, titleScreen);
	}
	else
	{
		gameBackground.drawBackground(gameWindow);

		present.drawPresent(gameWindow);

		player.Animate();
		player.DrawShip(gameWindow, deltaTime.asSeconds());
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);
		player.DrawAvailableMissile_OnTheScreen(gameWindow, resourceLoader.GetTexture(ResourceLoader::TextureType::UI_rocket));

		//Draw all bullets
		for (int i = 0; i < GameBullets.size(); i++)
			GameBullets[i].DrawBullet(gameWindow);

		//Draw all the eggs
		for (int index = 0; index < eggs.size(); index++)
			eggs[index].DrawEgg(gameWindow);

		for (int index = 0; index < explosions.size(); index++)
		{
			if (explosions[index].draw_explosion(gameWindow) == false)
				explosions.erase(explosions.begin() + index);
		}

		for (int index = 0; index < meat.size(); index++)
		{
			meat[index].Draw(gameWindow);
		}

		if (wave_number == 1)
		{
			//DRAW CHICKENS
			for (int index = 0; index < chickens.size(); index++)
			{
				chickens[index].drawChicken(gameWindow);
			}
		}
		else if (wave_number == 3)
		{
			//Draw all asteroids
			for (int index = 0; index < asteroids.size(); index++)
				asteroids[index].draw_asteroid(gameWindow);
		}
	}

	if (selected)
	{
		if (!start_game)
			titleScreen.menu_Select(gameWindow, titleScreen, selected);
	}
	else
	{
		if (!start_game)
			titleScreen.menu_Select(gameWindow, titleScreen, selected);
	}

	gameWindow.display();
}
