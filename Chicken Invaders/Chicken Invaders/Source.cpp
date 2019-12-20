#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "../LeaderboardDataSaver/DataSaver.h"

#include "ResourceLoader.h"
#include "Wave.h"
#include "ScrollBackground.h"
#include "Player.h"
#include "Chicken.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Present.h"
#include "Egg.h"
#include "Bullet.h"
#include "TitleScreen.h"
#include "Missile.h"
#include "Meat.h"
#include "Earth.h"
#include "RectangularBoundaryCollision.hpp"
#include "PauseMenu.h"
#include "Boss.h"
#include "Leaderboard.h"
using namespace sf;

#pragma region Methods

void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);

void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& mainMenuLeaderboardSelected, Player& player, ResourceLoader& resourceLoader, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, Wave& waveManager, Earth& earth, bool& isPaused, PauseMenu& pauseMenu, int& pause_selected, std::vector<Boss>& gameBosses, bool& leaderboardIsActive, std::vector<Present>& presents, std::vector<Egg>& eggs, Clock& clock, bool& endGame, std::string& playerName, DataSaver& dataSaver, Leaderboard& leaderboard, bool& savePlayerData);

void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Time& deltaTime, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, std::vector<Present>& presents, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, ResourceLoader& resourceLoader, Wave& waveManager, Earth& earth, bool& isPaused, PauseMenu& pauseMenu, RenderWindow& gameWindow, std::vector<Boss> &gameBosses);

void CheckCollisions(ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Chicken>& chickens, std::vector<Present>& presents, bool& isPaused, std::vector<Boss>& gameBosses);

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, std::vector<Present>& presents, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, Earth& earth, PauseMenu& pauseMenu, bool& isPaused, int& pause_selected, std::vector<Boss>& gameBosses, bool leaderboardIsActive, Leaderboard& leaderboardPanel, bool endGame, Text gameOverText, std::string& playerName);

bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Earth& earth, PauseMenu& pauseMenu, Leaderboard& leaderboardPanel, Text& gameOverText, DataSaver& dataSaver);

bool CheckSpriteCollision(const sf::Sprite& oneSprite, const sf::Sprite& anotherSprite);

void ResetGame(Clock& clock, int& wave_number, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Meat>& meat, std::vector<Boss>& gameBosses, std::vector<Missile>& gameMissiles, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, std::vector<Present>& presents, int& Contor, Player& player, bool& start_game, bool& isPaused, bool& endGame, bool& savePlayerData);
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

	bool mainMenuLeaderboardSelected = true;
	bool start_game = false;
	TitleScreen titleScreen;
	PauseMenu pauseMenu;


	Earth earth;
	Player player;
	ScrollBackground gameBackground;
	std::vector<Bullet> GameBullets;	//Gloantele din joc
	int Contor = 0;						//Contor folosit pentru teste
	std::vector<Missile>gameMissiles;
	std::vector<Boss> gameBosses;
	//Vector that will hold all the eggs on the screen, when the exit the screen or collide we take them out.
	std::vector<Egg> eggs;
	//Vector that will contain all the asteroids
	std::vector<Asteroid> asteroids;
	//Vector of chickens
	std::vector<Chicken> chickens;
	std::vector<Explosion> explosions;

	std::vector<Meat> meat;

	Leaderboard leaderboardPanel;
	DataSaver dataSaver;
	std::string playerName;
	bool leaderboardIsActive = false;

	bool endGame = false;
	Time playerDeathTime;
	float gameOverTextTime = 5.0f;
	Text gameOverText;
	bool savePlayerData = false;

	bool isPaused = false;
	int pause_selected = 1;
#pragma endregion

	if (Init(WINDOW_WIDTH, WINDOW_HEIGHT, gameWindow, clock, resourceLoader, loadingText, titleScreen, gameBackground, player, earth,pauseMenu, leaderboardPanel, gameOverText, dataSaver) == false)
		return;

	lastFrameTime = clock.getElapsedTime();

	//Game widow
	while (gameWindow.isOpen())
	{
		deltaTime = clock.getElapsedTime() - lastFrameTime;
		lastFrameTime = clock.getElapsedTime();
	
		CheckInput(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, start_game, mainMenuLeaderboardSelected, player, resourceLoader, Contor, GameBullets, meat,gameMissiles,asteroids, chickens, waveManager, earth,isPaused, pauseMenu,pause_selected,gameBosses, leaderboardIsActive, presents, eggs, clock, endGame, playerName, dataSaver, leaderboardPanel, savePlayerData);

		Movement(WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, deltaTime, gameBackground, player, eggs, chickens, presents, asteroids,GameBullets, meat,gameMissiles,resourceLoader, waveManager, earth,isPaused,pauseMenu,gameWindow,gameBosses);
		CheckCollisions(resourceLoader, player, Contor, eggs, asteroids, GameBullets, explosions, meat,gameMissiles,chickens,presents,isPaused,gameBosses);

		if (player.IsDead() && endGame == false)
		{
			endGame = true;
			playerDeathTime = clock.getElapsedTime();
		}

		DrawEverything(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, resourceLoader, titleScreen, gameBackground, player, presents, chickens, asteroids, GameBullets, eggs, mainMenuLeaderboardSelected, start_game, deltaTime, explosions, meat,gameMissiles, earth,pauseMenu,isPaused,pause_selected,gameBosses, leaderboardIsActive, leaderboardPanel, endGame, gameOverText, playerName);

		if (endGame && leaderboardIsActive == false)
		{
			playerDeathTime -= deltaTime;
			if (clock.getElapsedTime().asSeconds() - playerDeathTime.asSeconds() > gameOverTextTime)
			{
				leaderboardIsActive = true;
				savePlayerData = true;
			}
		}
	}
}

void ResetGame(Clock& clock, int& wave_number, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Meat>& meat, std::vector<Boss>& gameBosses, std::vector<Missile>& gameMissiles, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, std::vector<Present>& presents, int& Contor, Player& player, bool& start_game, bool& isPaused, bool& endGame, bool& savePlayerData)
{
	clock.restart();
	wave_number = 0;

	chickens.clear();
	asteroids.clear();
	meat.clear();
	gameBosses.clear();
	gameMissiles.clear();
	GameBullets.clear();
	eggs.clear();
	presents.clear();
	Contor = 0;
	player.Reset();

	start_game = false;
	isPaused = false;
	endGame = false;
	savePlayerData = false;
}

bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Earth& earth, PauseMenu& pauseMenu, Leaderboard& leaderboardPanel, Text& gameOverText, DataSaver& dataSaver)
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
	pauseMenu.PauseMenu_SetTextures(WINDOW_WIDTH, WINDOW_HEIGHT, resourceLoader);
	pauseMenu.PauseMenu_ChangeSelection(1);
	earth.Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Earth));

	player.LoadLiveSprites(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_heart));
	player.SetUpScore(resourceLoader.GetFont());

	dataSaver.LoadData();
	leaderboardPanel.Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Leaderboard), resourceLoader.GetFont(), WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int index = 0; index < 10; index++)
	{
		leaderboardPanel.SetPlayerData(index, dataSaver.GetPlayerName(index), dataSaver.GetPlayerScore(index));
	}

	gameOverText.setFont(resourceLoader.GetFont());
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(100);
	gameOverText.setPosition(WINDOW_WIDTH / 2 - gameOverText.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 - gameOverText.getLocalBounds().height / 2);

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

void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& mainMenuLeaderboardSelected, Player& player, ResourceLoader& resourceLoader, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, Wave& waveManager, Earth& earth, bool& isPaused, PauseMenu& pauseMenu, int& pause_selected, std::vector<Boss>& gameBosses, bool& leaderboardIsActive, std::vector<Present>& presents, std::vector<Egg>& eggs, Clock& clock, bool& endGame, std::string& playerName, DataSaver& dataSaver, Leaderboard& leaderboard, bool& savePlayerData)
{
	Event eventHandler;
	while (gameWindow.pollEvent(eventHandler))
	{
		if (savePlayerData == true && eventHandler.type == Event::TextEntered)
		{
			if (eventHandler.text.unicode == 8)
				playerName.pop_back();

			if (((eventHandler.text.unicode >= '0' && eventHandler.text.unicode <= '9') || (eventHandler.text.unicode >= 'a' && eventHandler.text.unicode <= 'z') || (eventHandler.text.unicode >= 'A' && eventHandler.text.unicode <= 'Z') || eventHandler.text.unicode == ' ') && playerName.size() < 20)
				playerName += eventHandler.text.unicode;
		}

		if (eventHandler.type == Event::KeyPressed)
		{
			if (eventHandler.key.code == Keyboard::Left)
			{
				if (!isPaused)
				{
					player.SetMovement(false, 1);
				}
			}
			if (eventHandler.key.code == Keyboard::Right)
			{
				if (!isPaused)
				{
					player.SetMovement(true, 1);
				}
			}
			if (eventHandler.key.code == Keyboard::Space || eventHandler.key.code == Keyboard::Enter || eventHandler.key.code == Keyboard::Z)
			{
				if (start_game == false)
				{
					if (eventHandler.key.code == Keyboard::Space)
					{
						wave_number = 1;
						start_game = true;
					}
					else
					{
						if (mainMenuLeaderboardSelected == false)
							gameWindow.close();
						else
							leaderboardIsActive = true;
					}
				}
				if (isPaused)
				{
					if (pause_selected == 1)
					{
						leaderboardIsActive = true;
					}
					if (pause_selected == 2)
					{
						ResetGame(clock, wave_number, chickens, asteroids, meat, gameBosses, gameMissiles, GameBullets, eggs, presents, Contor, player, start_game, isPaused, endGame, savePlayerData);
					}
					if (pause_selected == 3)
						gameWindow.close();
				}
				if (savePlayerData == true && eventHandler.key.code == Keyboard::Enter)
				{
					savePlayerData = false;
					dataSaver.SaveData(playerName, player.GetScore());
					playerName = "";
					for (int index = 0; index < 10; index++)
					{
						leaderboard.SetPlayerData(index, dataSaver.GetPlayerName(index), dataSaver.GetPlayerScore(index));
					}
				}
			}
			if (eventHandler.key.code == Keyboard::Escape)
			{
				if (leaderboardIsActive)
				{
					if(endGame == true)
						ResetGame(clock, wave_number, chickens, asteroids, meat, gameBosses, gameMissiles, GameBullets, eggs, presents, Contor, player, start_game, isPaused, endGame, savePlayerData);
					leaderboardIsActive = false;
				}
				else if (start_game && endGame == false)
				{
					if (!isPaused)
					{
						isPaused = true;
					}
					else
					{
						isPaused = false;
					}
				}
			}
			if (eventHandler.key.code == Keyboard::Up)
			{
				if (leaderboardIsActive == false)
				{
					if (isPaused)
					{
						pause_selected--;
						if (pause_selected < 1)
							pause_selected = 1;
						pauseMenu.PauseMenu_ChangeSelection(pause_selected);
					}
					if (start_game == false)
					{
						mainMenuLeaderboardSelected = true;
					}
				}
			}
			if (eventHandler.key.code == Keyboard::Down)
			{
				if (leaderboardIsActive == false)
				{
					if (isPaused)
					{
						pause_selected++;
						if (pause_selected > 3)
							pause_selected = 3;
						pauseMenu.PauseMenu_ChangeSelection(pause_selected);
					}
					if (start_game == false)
					{
						mainMenuLeaderboardSelected = false;
					}
				}
			}
			if (eventHandler.key.code == Keyboard::Num1 || eventHandler.key.code == Keyboard::Num2)
			{
				wave_number = 1;
				earth.Reset();
				asteroids.clear();
				chickens.clear();
				gameBosses.clear();
				waveManager.Wave1Init(chickens, resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken), WINDOW_WIDTH, WINDOW_HEIGHT);
				waveManager.Wave1SetPosition(chickens, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
			if (eventHandler.key.code == Keyboard::Num3)
			{
				earth.Reset();
				wave_number = 3;
				chickens.clear();
				asteroids.clear();
				gameBosses.clear();
				if (wave_number / 10 % 10 % 2 == 0)
					waveManager.Wave3Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid), asteroids);
				else if (wave_number / 10 % 10 % 2 != 0)
					waveManager.Wave3Init(resourceLoader.GetTexture(ResourceLoader::TextureType::AsteroidFlame), asteroids);

			}
			//Wave Testing
			if (eventHandler.key.code == Keyboard::Num4 || eventHandler.key.code == Keyboard::Num5)
			{
				earth.Reset();
				chickens.clear();
				asteroids.clear();
				gameBosses.clear();
				earth.SetPosition(sf::Vector2f(WINDOW_WIDTH / 2, 0));
				earth.SetTarget(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3));
				wave_number = 4;
			}
			if (eventHandler.key.code == Keyboard::Num6)
			{
				chickens.clear();
				asteroids.clear();
				gameBosses.clear();
				if (wave_number / 10 % 10 % 2 != 0)
					waveManager.wave6Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid)
						, WINDOW_WIDTH, WINDOW_HEIGHT);
				else if (wave_number / 10 % 10 % 2 == 0)
					waveManager.wave6Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::AsteroidFlame)
						, WINDOW_WIDTH, WINDOW_HEIGHT);
				wave_number = 6;
			}
			if (eventHandler.key.code == Keyboard::Num7)
			{
				wave_number = 7;
				earth.Reset();
				asteroids.clear();
				chickens.clear();
				gameBosses.clear();
				waveManager.Wave7Init(chickens, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT);

			}
			if (eventHandler.key.code == Keyboard::Num8)
			{
				wave_number = 8;
				earth.Reset();
				asteroids.clear();
				chickens.clear();
				gameBosses.clear();
				waveManager.Wave8Init(chickens, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
			if (eventHandler.key.code == Keyboard::Num9)
			{
				wave_number = 9;
				earth.Reset();
				asteroids.clear();
				chickens.clear();
				gameBosses.clear();
				if (wave_number / 10 % 10 % 2 != 0)
					waveManager.Wave9Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid)
						, WINDOW_WIDTH, WINDOW_HEIGHT);
				else if (wave_number / 10 % 10 % 2 == 0)
					waveManager.Wave9Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::AsteroidFlame)
						, WINDOW_WIDTH, WINDOW_HEIGHT);
			
			}
			if (eventHandler.key.code == Keyboard::Num0)
			{
				wave_number = 10;
				earth.Reset();
				asteroids.clear();
				chickens.clear();
				gameBosses.clear();
				waveManager.Wave10Init(gameBosses, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT);
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
				if (!isPaused && player.IsDead() == false)
				{
					Bullet x(player.GetPosition().x, player.GetPosition().y, resourceLoader.GetTexture(ResourceLoader::TextureType::Bullet));
					for (int i = 0; i < Contor; i++)
					{
						x.Present_Collected();
					}
					GameBullets.push_back(std::move(x));
				}
				
			}
			if (eventHandler.key.code == Keyboard::X)
			{
				if (player.IsDead() == false && player.GetNrMissiles() > 0)
				{
					Missile missile(player.GetPosition().x, player.GetPosition().y, resourceLoader.GetTexture(ResourceLoader::TextureType::Rocket));
					gameMissiles.push_back(std::move(missile));
					player.ShootMissile();
				}
			}
		} 
	
	}
}

void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Time& deltaTime, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, std::vector<Present>& presents, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, ResourceLoader& resourceLoader, Wave& waveManager, Earth& earth,bool& isPaused,PauseMenu& pauseMenu, RenderWindow& gameWindow, std::vector<Boss>& gameBosses)
{
	gameBackground.AnimateBackground();
	player.MoveShip(WINDOW_WIDTH);
	//Move each egg from the eggs vector
	if (!isPaused)
	{
		for (int index = 0; index < eggs.size(); index++)
			if (eggs[index].FallDown(WINDOW_HEIGHT) == false)
				eggs.erase(eggs.begin() + index);

		for (int index = 0; index < meat.size(); index++)
			if (meat[index].Move(WINDOW_WIDTH, WINDOW_HEIGHT, deltaTime.asSeconds()) == false)
				meat.erase(meat.begin() + index);
	}
	
		

	//BulletMovement
	if (!isPaused)
	for (int i = 0; i < GameBullets.size(); i++)
	{
		GameBullets[i].BulletsPosition_Update();
		if (GameBullets[i].CheckIfBulletIsOnTheScreen(WINDOW_HEIGHT) == true)
			GameBullets.erase(GameBullets.begin() + i);
	}
	//Missile Movment
	for (int i = 0; i < gameMissiles.size(); i++)
	{
		if (!isPaused)
			gameMissiles[i].UpdatePosition(player.GetPosition().x);
	}
	if (wave_number == 1)
	{
		
		if (!isPaused)
			waveManager.Wave1Movement(chickens);
	}
	if (wave_number == 3)
	{
		if (!isPaused)
		{
			for (int index = 0; index < asteroids.size(); index++)
			{
				if (asteroids[index].Falldown(WINDOW_HEIGHT, asteroids[index].getasteroidsSpeed()-10, asteroids[index].getasteroidsSpeed()-10))
					asteroids.erase(asteroids.begin() + index);
			}
		}
		
	}
	if (wave_number == 4 || wave_number == 5)
	{
		if (!isPaused)
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
		
	}
	if (wave_number == 6)
	{
		if(!isPaused)
			waveManager.wave6Movement(asteroids, WINDOW_WIDTH, WINDOW_HEIGHT);

	}
	if (wave_number == 7)
	{
		if (!isPaused)
			waveManager.Wave7Movement(chickens, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	if (wave_number == 8)
	{
		if (!isPaused)
			waveManager.Wave8Movement(chickens, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	if (wave_number == 9)
	{
		if (!isPaused)
			waveManager.Wave9Movement(asteroids, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	if (wave_number == 10)
	{
		if (!isPaused)
			waveManager.Wave10Movement(gameBosses, WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	if (!isPaused)
		for (int i = 0; i < presents.size(); i++)
			presents[i].FallDownPresent(WINDOW_HEIGHT);
}

void CheckCollisions(ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Chicken>& chickens, std::vector<Present>& presents,bool& isPaused, std::vector<Boss>& gameBosses)
{
	if (player.IsDead() == false)
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
					if (Contor > 1)
						Contor--;
				}
			}
		//check if the asteroids colide with ship 
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
		//check the colision with the meat and present
		for (int index = 0; index < meat.size(); index++)
			if (CheckSpriteCollision(player.GetSprite(), meat[index].GetSprite()))
			{
				player.UpdateScore(meat[index].getMeatScore());
				meat.erase(meat.begin() + index);
				player.AddMeat();
			}
		for (int i = 0; i < presents.size(); i++)
			if (CheckSpriteCollision(player.GetSprite(), presents[i].GetSprite()))
			{
				presents.erase(presents.begin() + i);
				Contor++;
			}
	}
	//check the colision of asteroids with bullet
	for (int index = 0; index < asteroids.size(); index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for (int z = 0; z < 7; z++)
				if (GameBullets[j].GetState(z) == true)
					if (CheckSpriteCollision(GameBullets[j].GetSprite(z), asteroids[index].GetSprite()))
					{
						player.UpdateScore(asteroids[index].getScore());
						explosions.push_back(Explosion());
						explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
						explosions[explosions.size() - 1].explosion_setPosition(asteroids[index].GetPosition().x + 100, asteroids[index].GetPosition().y + 70);
						asteroids.erase(asteroids.begin() + index);
						GameBullets[j].SetStateFalse(z);
						z = 7;
						j = GameBullets.size();
					}
	//check the colision of chickens with bullets
	for (int index = 0; index < chickens.size(); index++)
	{//seteaza viata la 2 
		chickens[index].setChickenLife(1);
		for (int j = 0; j < GameBullets.size(); j++)

			for (int z = 0; z < 7; z++)
				// cred ca e din cauza conditiei de orprire
				if ( GameBullets[j].GetState(z) == true) {
					
				
					if (CheckSpriteCollision(GameBullets[j].GetSprite(z), chickens[index].GetSprite()))
					{
						chickens[index].setChickenLife(chickens[index].getChickenLife() - 1);
						//daca pun state la game bullets false le reduce viata doar cu 1, dar daca nu o fac bulletul trece prin toate gainile 
						//GameBullets[j].SetStateFalse(z);
						
						std::cout << chickens[index].getChickenLife()<<" ";
						if (chickens[index].getChickenLife() == 0)
						{
							player.UpdateScore(chickens[index].getChickenScore());
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
					}
					
				

				}
	}
	for (int index = 0; index < gameBosses.size(); index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for (int z = 0; z < 7; z++)
				if (GameBullets[j].GetState(z) == true)
					if (CheckSpriteCollision(GameBullets[j].GetSprite(z), gameBosses[index].GetSprite()))
					{
						player.UpdateScore(gameBosses[index].GetScore());
						
					if (gameBosses[index].GetLife() == 1)
						{
						player.UpdateScore(gameBosses[index].GetScore()*10);
							explosions.push_back(Explosion());
							explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
							explosions[explosions.size() - 1].explosion_setPosition(gameBosses[index].GetPosition().x-200, gameBosses[index].GetPosition().y-100);
							explosions[explosions.size() - 1].explosion_setScale(3, 3);	
							for (int a = 0; a < 30; a++)
							{
								Meat meatClone(sf::Vector2f(gameBosses[index].GetPosition().x+200, gameBosses[index].GetPosition().y +300), resourceLoader.GetTexture(ResourceLoader::TextureType::Meat));
								meat.push_back(std::move(meatClone));

							}
							gameBosses.erase(gameBosses.begin() + index);
						}
						else
							gameBosses[index].ByeByeBoss();
						GameBullets[j].SetStateFalse(z);
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
	if (!isPaused)
	{
		for (int i = 0; i < chickens.size(); i++)
		{
			int random = std::rand() % 500;
			if (random == 23)
			{
				Egg clone(sf::Vector2f(chickens[i].getPosition().x + 40, chickens[i].getPosition().y + 50), resourceLoader.GetTexture(ResourceLoader::TextureType::Egg));
				eggs.push_back(std::move(clone));
			}
		}
		for (int i = 0; i < gameBosses.size(); i++)
		{
			int randomPoz = std::rand() % 200+100;
			int random = std::rand() % 10;
			if (random == 4)
			{
				
				Egg clone(sf::Vector2f(gameBosses[i].GetPosition().x+randomPoz, gameBosses[i].GetPosition().y+500), resourceLoader.GetTexture(ResourceLoader::TextureType::Egg));
				eggs.push_back(std::move(clone));
			}

		}
	}
}

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, std::vector<Present>& presents, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, Earth& earth,PauseMenu& pauseMenu,bool& isPaused,int& pause_selected, std::vector<Boss>& gameBosses, bool leaderboardIsActive, Leaderboard& leaderboardPanel, bool endGame, Text gameOverText, std::string& playerName)
{
	gameWindow.clear();
	if (wave_number == 0)
	{
		titleScreen.IntroMain_Display(gameWindow, titleScreen);
	}
	else
	{
		gameBackground.drawBackground(gameWindow);
		
		if (player.IsDead() == false)
		{
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
		}

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
		for (int i = 0; i < gameBosses.size(); i++)
			gameBosses[i].DrawBoss(gameWindow);

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
	if (isPaused)
	{
		pauseMenu.PauseMenu_Display(gameWindow, pauseMenu);
	}

	if (endGame)
	{
		gameWindow.draw(gameOverText);
		if (leaderboardIsActive)
			leaderboardPanel.SetInputPlayerName(playerName);
	}
	if (leaderboardIsActive)
		leaderboardPanel.Draw(gameWindow);

	gameWindow.display();
}
