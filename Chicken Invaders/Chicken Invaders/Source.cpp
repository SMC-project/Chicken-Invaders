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
#include "Earth.h"
#include "RectangularBoundaryCollision.hpp"
using namespace sf;

#pragma region Methods

void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);

void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& selected, Player& player, ResourceLoader& resourceLoader, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, Wave& waveManager, Earth& earth);

void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Time& deltaTime, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, std::vector<Present>& presents, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, ResourceLoader& resourceLoader, Wave& waveManager, Earth& earth);

void CheckCollisions(ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Chicken> &chickens, std::vector<Present>& presents);

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, std::vector<Present>& presents, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, Earth& earth);

bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Earth& earth);

bool CheckSpriteCollision(const sf::Sprite& oneSprite, const sf::Sprite& anotherSprite);
#pragma endregion

int main()
{
	srand(std::time(NULL));

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
	Wave waveManager;
	ResourceLoader resourceLoader;
	sf::Text loadingText;

	int wave_number = 0;
	std::vector<Present> presents;

	bool selected = true;
	bool start_game = false;
	TitleScreen titleScreen;

	Earth earth;
	Player player;
	ScrollBackground gameBackground;
	std::vector<Bullet> GameBullets;	//Gloantele din joc
	int Contor = 0;						//Contor folosit pentru teste
	std::vector<Missile>gameMissiles;
	//Vector that will hold all the eggs on the screen, when the exit the screen or collide we take them out.
	std::vector<Egg> eggs;
	//Vector that will contain all the asteroids
	std::vector<Asteroid> asteroids;
	//Vector of chickens
	std::vector<Chicken> chickens;
	std::vector<Explosion> explosions;

	std::vector<Meat> meat;

#pragma endregion

	if (Init(WINDOW_WIDTH, WINDOW_HEIGHT, gameWindow, clock, resourceLoader, loadingText, titleScreen, gameBackground, player, earth) == false)
		return;

	lastFrameTime = clock.getElapsedTime();

	//Game widow
	while (gameWindow.isOpen())
	{
		deltaTime = clock.getElapsedTime() - lastFrameTime;
		lastFrameTime = clock.getElapsedTime();

		CheckInput(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, start_game, selected, player, resourceLoader, Contor, GameBullets, meat,gameMissiles,asteroids, chickens, waveManager, earth);

		Movement(WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, deltaTime, gameBackground, player, eggs, chickens, presents, asteroids,GameBullets, meat,gameMissiles,resourceLoader, waveManager, earth);
		CheckCollisions(resourceLoader, player, Contor, eggs, asteroids, GameBullets, explosions, meat,gameMissiles,chickens,presents);

		DrawEverything(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, resourceLoader, titleScreen, gameBackground, player, presents, chickens, asteroids, GameBullets, eggs, selected, start_game, deltaTime, explosions, meat,gameMissiles, earth);
	}
}

bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Earth& earth)
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

	player.Init(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8), resourceLoader.GetTexture(ResourceLoader::TextureType::Ship), resourceLoader.GetTexture(ResourceLoader::TextureType::UI_rocket));
	gameBackground.Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Background));

	resourceLoader.GetMusic().play();

	titleScreen.IntroMain_SetTextures(WINDOW_WIDTH, WINDOW_HEIGHT, resourceLoader);

	earth.Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Earth));

	player.LoadLiveSprites(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_heart));
	player.SetUpScore(resourceLoader.GetFont());

	gameWindow.clear();

	time = clock.getElapsedTime();
	std::cout << "Starting game: " << time.asSeconds() << "\n";

	return true;
}

bool CheckSpriteCollision(const sf::Sprite& oneSprite, const sf::Sprite& anotherSprite)
{
	if (collision::areColliding(oneSprite, anotherSprite))
		return true;
	return false;

}

void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& selected, Player& player, ResourceLoader& resourceLoader, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, Wave& waveManager, Earth& earth)
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
			if (eventHandler.key.code == Keyboard::Enter)
			{
				if (selected == false)
					gameWindow.close();
			}

			if (eventHandler.key.code == Keyboard::Num1 || eventHandler.key.code == Keyboard::Num2)
			{
				wave_number = 1;
				earth.Reset();
				asteroids.clear();
				chickens.clear();
				waveManager.Wave1Init(chickens, resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken), WINDOW_WIDTH, WINDOW_HEIGHT);
				waveManager.Wave1SetPosition(chickens, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
			if (eventHandler.key.code == Keyboard::Num3)
			{
				earth.Reset();
				wave_number = 3;
				chickens.clear();
				asteroids.clear();
				waveManager.Wave3Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid), asteroids);
			}
			//Wave Testing
			if (eventHandler.key.code == Keyboard::Num4 || eventHandler.key.code == Keyboard::Num5)
			{
				earth.Reset();
				chickens.clear();
				asteroids.clear();
				earth.SetPosition(sf::Vector2f(WINDOW_WIDTH / 2, 0));
				earth.SetTarget(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3));
				wave_number = 4;
			}
			if (eventHandler.key.code == Keyboard::Num6)
			{
				chickens.clear();
				asteroids.clear();
				waveManager.wave6Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid)
					, WINDOW_WIDTH, WINDOW_HEIGHT);
				wave_number = 6;
			}
		}
		if (eventHandler.type == Event::KeyReleased)
		{
			if (eventHandler.key.code == Keyboard::Left)
				player.SetMovement(false, 0);
			if (eventHandler.key.code == Keyboard::Right)
				player.SetMovement(true, 0);
			if (eventHandler.key.code == Keyboard::Z)
			{
				Bullet x(player.GetPosition().x, player.GetPosition().y, resourceLoader.GetTexture(ResourceLoader::TextureType::Bullet));
				for (int i = 0; i < Contor; i++)
				{
					x.Present_Collected();
				}
				GameBullets.push_back(std::move(x));
			}
			if (eventHandler.key.code == Keyboard::X)
			{
				if (player.GetNrMissiles() > 0)
				{
					Missile missile(player.GetPosition().x, player.GetPosition().y, resourceLoader.GetTexture(ResourceLoader::TextureType::Rocket));
					gameMissiles.push_back(std::move(missile));
					player.ShootMissile();
				}
			}
		} 
	
	}
}

void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Time& deltaTime, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, std::vector<Present>& presents, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, ResourceLoader& resourceLoader, Wave& waveManager, Earth& earth)
{
	gameBackground.AnimateBackground();
	player.MoveShip(WINDOW_WIDTH);
	//Move each egg from the eggs vector
	for (int index = 0; index < eggs.size(); index++)
		if (eggs[index].FallDown(WINDOW_HEIGHT) == false)
			eggs.erase(eggs.begin() + index);

	for (int index = 0; index < meat.size(); index++)
		if (meat[index].Move(WINDOW_WIDTH, WINDOW_HEIGHT, deltaTime.asSeconds()) == false)
			meat.erase(meat.begin() + index);

	//BulletMovement
	for (int i = 0; i < GameBullets.size(); i++)
	{
		GameBullets[i].BulletsPosition_Update();
		if (GameBullets[i].CheckIfBulletIsOnTheScreen(WINDOW_HEIGHT) == true)
			GameBullets.erase(GameBullets.begin() + i);
	}
	//Missile Movment
	for (int i = 0; i < gameMissiles.size(); i++)
	{
		gameMissiles[i].UpdatePosition(player.GetPosition().x);
	}
	if (wave_number == 1)
	{
		waveManager.Wave1Movement(chickens);
	}
	if (wave_number == 3)
	{
		for (int index = 0; index < asteroids.size(); index++)
		{
			if (asteroids[index].Falldown(WINDOW_HEIGHT,10,10))
				asteroids.erase(asteroids.begin() + index);
		}
	}
	if (wave_number == 4 || wave_number == 5)
	{
		earth.Move();
		if (earth.WaveHasStarted() == false && earth.FinishedMoving() == true)
		{
			earth.SetWaveHasStarted(true);
			waveManager.Wave4And5Init(chickens, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT);
		}
		waveManager.Wave4And5Movement(chickens, WINDOW_WIDTH, WINDOW_HEIGHT);

		if (earth.WaveHasStarted() == true && chickens.size() == 0)
			earth.SetTarget(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT + earth.GetSize().y));
	}
	if (wave_number == 6)
	{
		waveManager.wave6Movement(asteroids, WINDOW_WIDTH, WINDOW_HEIGHT);

	}

	for (int i = 0; i < presents.size(); i++)
		presents[i].FallDownPresent(WINDOW_HEIGHT);
}

void CheckCollisions(ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Chicken>& chickens, std::vector<Present>& presents)
{
	//Check if any of the eggs collides with the ship
	for (int index = 0; index < eggs.size(); index++)
		if (CheckSpriteCollision(player.GetSprite(), eggs[index].GetSprite()))
		{
			if (player.IsPlayerDead() == false)
			{
				//If so erase the egg and kill the player
				eggs.erase(eggs.begin() + index);

				explosions.push_back(Explosion());
				explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
				explosions[explosions.size() - 1].explosion_setPosition(player.GetPosition().x, player.GetPosition().y);
				player.Die();
				if(Contor > 1)
					Contor--;
			}
		}

	for (int index = 0; index < asteroids.size(); index++)
		if (CheckSpriteCollision(player.GetSprite(), asteroids[index].GetSprite()))
		{
			if (player.IsPlayerDead() == false)
			{
				//If so erase the asteroid and kill the player
				asteroids.erase(asteroids.begin() + index);

				explosions.push_back(Explosion());
				explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
				explosions[explosions.size() - 1].explosion_setPosition(player.GetPosition().x, player.GetPosition().y);

				player.Die();
				if (Contor > 1)
					Contor--;
			}
		}

	for (int index = 0; index < meat.size(); index++)
		if (CheckSpriteCollision(player.GetSprite(), meat[index].GetSprite()))
		{
			meat.erase(meat.begin() + index);
			player.AddMeat();
		}
	for (int i = 0; i < presents.size(); i++)
		if (CheckSpriteCollision(player.GetSprite(), presents[i].GetSprite()))
		{
			presents.erase(presents.begin() + i);
			Contor++;
		}

	for (int index = 0; index < asteroids.size(); index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for (int z = 0; z < 7; z++)
				if (GameBullets[j].GetState(z) == true)
					if (CheckSpriteCollision(GameBullets[j].GetSprite(z), asteroids[index].GetSprite()))
					{
						explosions.push_back(Explosion());
						explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
						explosions[explosions.size() - 1].explosion_setPosition(asteroids[index].GetPosition().x + 100, asteroids[index].GetPosition().y + 70);
						asteroids.erase(asteroids.begin() + index);
						GameBullets[j].SetStateFalse(z);
						z = 7;
						j = GameBullets.size();
					}
	for (int index = 0; index < chickens.size(); index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for (int z = 0; z < 7; z++)
				if (GameBullets[j].GetState(z) == true)
					if (CheckSpriteCollision(GameBullets[j].GetSprite(z), chickens[index].GetSprite()))
					{
						explosions.push_back(Explosion());
						explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
						explosions[explosions.size() - 1].explosion_setPosition(chickens[index].getPosition().x, chickens[index].getPosition().y - 20);
						Meat meatClone(sf::Vector2f(chickens[index].getPosition().x - 10, chickens[index].getPosition().y - 20), resourceLoader.GetTexture(ResourceLoader::TextureType::Meat));
						meat.push_back(std::move(meatClone));
						GameBullets[j].SetStateFalse(z);
						int random = rand() % 30;
						if (random == 3)
						{
							Present presentClone(sf::Vector2f(chickens[index].getPosition().x - 10, chickens[index].getPosition().y - 20), resourceLoader.GetTexture(ResourceLoader::TextureType::Gift));
							presents.push_back(std::move(presentClone));
						}
						chickens.erase(chickens.begin() + index);
						z = 7;
						j = GameBullets.size();
					}
	for (int i = 0; i < gameMissiles.size(); i++)
		if (gameMissiles[i].ItIsTimeForExplosion() == false)
		{
			explosions.push_back(Explosion());
			explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
			explosions[explosions.size() - 1].explosion_setPosition(300, -150);
			explosions[explosions.size() - 1].explosion_setScale(5, 5);
			gameMissiles.erase(gameMissiles.begin() + i);
			asteroids.clear();
			GameBullets.clear();
			chickens.clear();
			meat.clear();
			eggs.clear();
			presents.clear();
		}
	//Add random eggs

	for (int i = 0; i < chickens.size(); i++)
	{
		int random = std::rand() % 500;
		if (random == 23)
		{
			Egg clone(sf::Vector2f(chickens[i].getPosition().x + 40, chickens[i].getPosition().y + 50), resourceLoader.GetTexture(ResourceLoader::TextureType::Egg));
			eggs.push_back(std::move(clone));
		}
	}
}

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, std::vector<Present>& presents, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, Earth& earth)
{
	gameWindow.clear();
	if (wave_number == 0)
	{
		titleScreen.IntroMain_Display(gameWindow, titleScreen);
	}
	else
	{
		gameBackground.drawBackground(gameWindow);

		player.Animate();
		player.DrawShip(gameWindow, deltaTime.asSeconds());
		player.DrawLives(gameWindow);
		player.DrawScore(gameWindow);
		player.DrawUIMissile(gameWindow, resourceLoader.GetTexture(ResourceLoader::TextureType::UI_rocket));

		//Draw all bullets
		for (int i = 0; i < GameBullets.size(); i++)
			GameBullets[i].DrawBullet(gameWindow);

		//Draw all Missiles
		for (int i = 0; i < gameMissiles.size(); i++)
			gameMissiles[i].DrawMissile(gameWindow);

		//Draw all the eggs
		for (int index = 0; index < eggs.size(); index++)
			eggs[index].DrawEgg(gameWindow);

		for (int i = 0; i < presents.size(); i++)
			presents[i].DrawPresent(gameWindow);

		for (int index = 0; index < explosions.size(); index++)
			if (explosions[index].draw_explosion(gameWindow) == false)
				explosions.erase(explosions.begin() + index);

		for (int index = 0; index < meat.size(); index++)
			meat[index].Draw(gameWindow);

		for (int i = 0; i < chickens.size(); i++)
			chickens[i].drawChicken(gameWindow);

		for (int index = 0; index < asteroids.size(); index++)
			asteroids[index].draw_asteroid(gameWindow);

		if (wave_number == 4 || wave_number == 5)
		{
			earth.Draw(gameWindow);
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
