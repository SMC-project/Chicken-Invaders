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
using namespace sf;

#pragma region Methods

void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& selected, Player& player, ResourceLoader& resourceLoader, std::vector<Egg>& eggs, int& Contor, std::vector<Bullet>& GameBullets);
void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, Present& present, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets);
void CheckCollisions(Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets);
void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Explosion& explode, Present& present, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game);
bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Explosion& explode, Present& present, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens);

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
	ResourceLoader resourceLoader;
	sf::Text loadingText;

	Wave Wave1;
	Wave Wave3;
	int wave_number = 0;

	Explosion explode;
	Present present;

	bool selected = true;
	bool start_game = false;
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

#pragma endregion

	if (Init(WINDOW_WIDTH, WINDOW_HEIGHT, gameWindow, clock, resourceLoader, loadingText, titleScreen, gameBackground, player, explode, present, asteroids, chickens) == false)
		return;

	//Game widow
	while (gameWindow.isOpen())
	{
		CheckInput(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, start_game, selected, player, resourceLoader, eggs, Contor, GameBullets);

		Movement(WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, player, eggs, chickens, present, asteroids,GameBullets);
		CheckCollisions(player, Contor, eggs, asteroids,GameBullets);

		DrawEverything(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, titleScreen, gameBackground, player, explode, present, chickens, asteroids, GameBullets, eggs, selected, start_game);
	}
}

bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Explosion& explode, Present& present, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens)
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

	explode.setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
	present.setSpritePresent(resourceLoader.GetTexture(ResourceLoader::TextureType::Gift));

	player.LoadLiveSprites(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_heart));
	player.SetUpScore(resourceLoader.GetFont());

	float random_number;
	srand(std::time(NULL));
	for (int index = 0; index < 15; index++)
	{
		random_number = rand() % 900;
		random_number = -random_number;
		float current_x = random_number;

		random_number = rand() % 900;
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

void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& selected, Player& player, ResourceLoader& resourceLoader, std::vector<Egg>& eggs, int& Contor, std::vector<Bullet>& GameBullets)
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
			//This is only for testing purposes, delete it after implementing wave transition
			if (eventHandler.key.code == Keyboard::C)
			{
				if (wave_number == 1)
					wave_number = 3;
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

void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, Present& present, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets)
{
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
		for (int index = 0; index < asteroids.size(); index++)
		{
			if (asteroids[index].Falldown(WINDOW_HEIGHT))
				asteroids.erase(asteroids.begin() + index);
		}
	}

	present.fallDownPresent(WINDOW_HEIGHT);
}

void CheckCollisions(Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets)
{
	//Check if any of the eggs collides with the ship
	for (int index = 0; index < eggs.size(); index++)
		if (player.CheckCollision(eggs[index].GetPosition(), eggs[index].GetSize()))
		{
			//If so erase the egg and kill the player
			eggs.erase(eggs.begin() + index);
			player.Die();
			Contor--;
		}

	for (int index = 0; index < asteroids.size(); index++)
		if (player.CheckCollision(asteroids[index].GetPosition(), asteroids[index].GetSize()))
		{
			//If so erase the asteroid and kill the player
			asteroids.erase(asteroids.begin() + index);
			player.Die();
			Contor--;
		}
	/*for(int index=0;index<asteroids.size();index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for(int z=0;z<7;z++)
				if (GameBullets[j].CheckCollision(asteroids[index].GetPosition(), asteroids[index].GetSize(), z))
				{
					asteroids.erase(asteroids.begin() + index); 
				}*/


}

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Explosion& explode, Present& present, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game)
{
	gameWindow.clear();

	if (wave_number == 0)
	{
		titleScreen.IntroMain_Display(gameWindow, titleScreen);
	}
	if (wave_number == 1)
	{
		gameBackground.AnimateBackground();
		gameBackground.drawBackground(gameWindow);

		explode.explosion_setPosition(100, 100);
		explode.draw_explosion(gameWindow);

		present.drawPresent(gameWindow);

		player.Animate();
		player.DrawShip(gameWindow);
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);

		//DRAW CHICKENS
		for (int index = 0; index < chickens.size(); index++)
		{
			chickens[index].drawChicken(gameWindow);
		}
	}
	else if (wave_number == 3)
	{
		gameBackground.AnimateBackground();
		gameBackground.drawBackground(gameWindow);

		player.Animate();
		player.DrawShip(gameWindow);
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);

		//Draw all asteroids
		for (int index = 0; index < asteroids.size(); index++)
			asteroids[index].draw_asteroid(gameWindow);
	}
	
	//Draw all bullets
	for (int i = 0; i < GameBullets.size(); i++)
		GameBullets[i].DrawBullet(gameWindow);
		
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
		if (!start_game)
			titleScreen.menu_Select(gameWindow, titleScreen, selected);
	}

	gameWindow.display();
}
