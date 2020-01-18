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
#include "PauseMenu.h"
#include "Boss.h"
#include "Leaderboard.h"
#include"Feather.h"
#include "Networking.h"
#include "AI_Companion.h"
using namespace sf;

#pragma region Methods

void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, char playMode, char connectionMode, Networking& net);

void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& mainMenuLeaderboardSelected, Player& player, ResourceLoader& resourceLoader, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, Wave& waveManager, Earth& earth, bool& isPaused, PauseMenu& pauseMenu, int& pause_selected, std::vector<Boss>& gameBosses, bool& leaderboardIsActive, std::vector<Present>& presents, std::vector<Egg>& eggs, Clock& clock, bool& endGame, std::string& playerName, DataSaver& dataSaver, Leaderboard& leaderboard, bool& savePlayerData, int& waveTransition, bool& endWave, float& waveTime, std::vector<Feather>& feathers, Networking& net, char playMode, char connectionMode, bool& netCheckStartGame, AI_Companion& aiCompanion, uint32_t &scoreBeforeDeath);

void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Time& deltaTime, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, std::vector<Present>& presents, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, ResourceLoader& resourceLoader, Wave& waveManager, Earth& earth, bool& isPaused, PauseMenu& pauseMenu, RenderWindow& gameWindow, std::vector<Boss>& gameBosses, int& waveTransition, std::vector<Feather>& feathers, AI_Companion& aiCompanion, uint32_t &scoreBeforeDeath);

void CheckCollisions(Clock& clock, ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Chicken>& chickens, std::vector<Present>& presents, bool& isPaused, std::vector<Boss>& gameBosses, int wave_number, const Time& wave8StartTime, std::vector<Feather>& feathers, uint32_t &scoreBeforeDeath, AI_Companion &aiCompanion);

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, std::vector<Present>& presents, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, Earth& earth, PauseMenu& pauseMenu, bool& isPaused, int& pause_selected, std::vector<Boss>& gameBosses, bool leaderboardIsActive, Leaderboard& leaderboardPanel, bool endGame, Text gameOverText, std::string& playerName, bool& drawWaveNumber, Text textWaveNumber, std::vector<Feather>& feathers, AI_Companion& aiCompanion);

bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Earth& earth, PauseMenu& pauseMenu, Leaderboard& leaderboardPanel, Text& gameOverText, DataSaver& dataSaver, Text& textWaveNumber, AI_Companion& aiCompanion);

void CheckWaveTransition(int WINDOW_WIDTH, int WINDOW_HEIGHT, sf::Clock& clock, int& waveTransition, Text& textWaveNumber, bool& endWave, float& waveTime, bool& drawWaveNumber, Earth& earth, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, std::vector<Boss>& gameBosses, std::vector<Egg>& eggs, int& wave_number, Wave& waveManager, ResourceLoader& resourceLoader, Time& wave8StartTime);

bool CheckSpriteCollision(const sf::FloatRect& first, const sf::FloatRect& second);

void ResetGame(Clock& clock, int& wave_number, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Meat>& meat, std::vector<Boss>& gameBosses, std::vector<Missile>& gameMissiles, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, std::vector<Present>& presents, int& Contor, Player& player, bool& start_game, bool& isPaused, bool& endGame, bool& savePlayerData, int& waveTransition, bool& endWave, float& waveTime, std::vector<Feather>& feathers, AI_Companion& aiCompanion, uint32_t &scoreBeforeDeath);
#pragma endregion

int main()
{
	srand(std::time(NULL));

	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	Networking net;
	char playMode, connectionMode = 'c';
	std::cout << "How do you want to play?\n0 - single player\n1 - multiplayer\n\nUser choice: ";
	std::cin >> playMode;
	while (playMode != '0' && playMode != '1')
	{
		std::cout << "Wrong input, try again: ";
		std::cin >> playMode;
	}
	if (playMode == '1')
	{
		std::cout << "Press (s) for server and (c) for client: ";
		std::cin >> connectionMode;
		while (connectionMode != 's' && connectionMode != 'c')
		{
			std::cout << "Wrong input, try again: ";
			std::cin >> connectionMode;
		}

		if (connectionMode == 's')
			net.ServerConnection();
		else
			net.ClientConnection();
	}

	system("pause");

	RenderWindow gameWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chicken Invaders DX", Style::Fullscreen);
	gameWindow.setFramerateLimit(30);

	GameLoop(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, playMode, connectionMode, net);

	return 0;
}

void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, char playMode, char connectionMode, Networking& net)
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

	float waveTime = 7;

	Earth earth;
	Player player;
	AI_Companion aiCompanion;
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
	std::vector<Feather> feathers;
	Leaderboard leaderboardPanel;
	DataSaver dataSaver;
	std::string playerName;
	bool leaderboardIsActive = false;

	bool endGame = false;
	Time playerDeathTime;
	float gameOverTextTime = 5.0f;
	Text gameOverText;
	Text textWaveNumber;
	bool drawWaveNumber = false;
	bool savePlayerData = false;

	bool isPaused = false;
	int pause_selected = 1;
	int waveTransition = 0;
	bool endWave = true;
	uint32_t scoreBeforeDeath=0;
	Time waveStartTime;
#pragma endregion

	if (Init(WINDOW_WIDTH, WINDOW_HEIGHT, gameWindow, clock, resourceLoader, loadingText, titleScreen, gameBackground, player, earth, pauseMenu, leaderboardPanel, gameOverText, dataSaver, textWaveNumber,aiCompanion) == false)
		return;

	lastFrameTime = clock.getElapsedTime();
	std::string netReceivedData;

	sf::Time packetLastClearTime;
	packetLastClearTime = clock.getElapsedTime();

	bool netCheckStartGame = false;

	//Game widow
	while (gameWindow.isOpen())
	{
		deltaTime = clock.getElapsedTime() - lastFrameTime;
		lastFrameTime = clock.getElapsedTime();

		/*if (playMode == '1' && connectionMode == 'c' && net.ReceiveData())
		{
			net.packet >> netReceivedData;
			if (netReceivedData == "start game")
			{
				std::cout << "start game";
				wave_number = 1;
				waveTransition = 1;
				start_game = true;
			}
		}*/

		if (netCheckStartGame)
		{
			std::cout << "Check start game";
			net.ReceiveData();
			net.packet >> netReceivedData;
			if (netReceivedData == "start game")
			{
				std::cout << "start game";
				wave_number = 1;
				waveTransition = 1;
				start_game = true;
				netCheckStartGame = false;
				net.packet.clear();
			}
		}

		if (playMode == '1' && clock.getElapsedTime().asSeconds() - packetLastClearTime.asSeconds() > 2.5f)
		{
			packetLastClearTime = clock.getElapsedTime();
			net.packet.clear();

			netCheckStartGame = false;
		}

		CheckWaveTransition(WINDOW_WIDTH, WINDOW_HEIGHT, clock, waveTransition, textWaveNumber, endWave, waveTime, drawWaveNumber, earth, asteroids, chickens, gameBosses, eggs, wave_number, waveManager, resourceLoader, waveStartTime);

		CheckInput(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, start_game, mainMenuLeaderboardSelected, player, resourceLoader, Contor, GameBullets, meat, gameMissiles, asteroids, chickens, waveManager, earth, isPaused, pauseMenu, pause_selected, gameBosses, leaderboardIsActive, presents, eggs, clock, endGame, playerName, dataSaver, leaderboardPanel, savePlayerData, waveTransition, endWave, waveTime, feathers, net, playMode, connectionMode, netCheckStartGame,aiCompanion,scoreBeforeDeath);
		Movement(WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, deltaTime, gameBackground, player, eggs, chickens, presents, asteroids, GameBullets, meat, gameMissiles, resourceLoader, waveManager, earth, isPaused, pauseMenu, gameWindow, gameBosses, waveTransition, feathers,aiCompanion,scoreBeforeDeath);
		CheckCollisions(clock, resourceLoader, player, Contor, eggs, asteroids, GameBullets, explosions, meat, gameMissiles, chickens, presents, isPaused, gameBosses, wave_number, waveStartTime, feathers, scoreBeforeDeath,aiCompanion);

		if (player.IsDead() && endGame == false)
		{
			endGame = true;
			playerDeathTime = clock.getElapsedTime();
		}

		DrawEverything(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT, wave_number, resourceLoader, titleScreen, gameBackground, player, presents, chickens, asteroids, GameBullets, eggs, mainMenuLeaderboardSelected, start_game, deltaTime, explosions, meat, gameMissiles, earth, pauseMenu, isPaused, pause_selected, gameBosses, leaderboardIsActive, leaderboardPanel, endGame, gameOverText, playerName, drawWaveNumber, textWaveNumber, feathers,aiCompanion);

		if (endGame && leaderboardIsActive == false)
		{
			playerDeathTime -= deltaTime;
			if (clock.getElapsedTime().asSeconds() - playerDeathTime.asSeconds() > gameOverTextTime)
			{
				/*if (playMode == '1')
				{
					net.packet << "game over";
					net.SendData();

					net.ReceiveData();
					net.packet >> netReceivedData;
					if (netReceivedData == "game over")
					{
						leaderboardIsActive = true;
						savePlayerData = true;
					}
				}
				else
				{*/
					leaderboardIsActive = true;
					savePlayerData = true;
				//}
			}
		}
	}
}

void ResetGame(Clock& clock, int& wave_number, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Meat>& meat, std::vector<Boss>& gameBosses, std::vector<Missile>& gameMissiles, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, std::vector<Present>& presents, int& Contor, Player& player, bool& start_game, bool& isPaused, bool& endGame, bool& savePlayerData, int& waveTransition, bool& endWave, float& waveTime, std::vector<Feather>& feathers, AI_Companion& aiCompanion, uint32_t& scoreBeforeDeath)
{
	clock.restart();
	wave_number = 0;
	waveTime = 7;
	chickens.clear();
	asteroids.clear();
	meat.clear();
	feathers.clear();
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
	endWave = true;
	waveTransition = 0;
	scoreBeforeDeath = 0;
	aiCompanion.Reset();
	
}
bool Init(int WINDOW_WIDTH, int WINDOW_HEIGHT, RenderWindow& gameWindow, Clock& clock, ResourceLoader& resourceLoader, Text& loadingText, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, Earth& earth, PauseMenu& pauseMenu, Leaderboard& leaderboardPanel, Text& gameOverText, DataSaver& dataSaver, Text& textWaveNumber, AI_Companion& aiCompanion)
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
	aiCompanion.Init(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8), resourceLoader.GetTexture(ResourceLoader::TextureType::Ship));
	gameBackground.Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Background));

	resourceLoader.GetMusic().play();
	resourceLoader.GetMusic().setVolume(50);

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

	textWaveNumber.setFont(resourceLoader.GetFont());
	textWaveNumber.setString("");
	textWaveNumber.setCharacterSize(100);
	textWaveNumber.setPosition(WINDOW_WIDTH / 2 - textWaveNumber.getLocalBounds().width / 2, WINDOW_HEIGHT / 3 - textWaveNumber.getLocalBounds().height / 3);

	gameWindow.clear();

	time = clock.getElapsedTime();
	std::cout << "Starting game: " << time.asSeconds() << "\n";

	return true;
}


bool CheckSpriteCollision(const sf::FloatRect& first, const sf::FloatRect& second)
{
	if (first.intersects(second))
		return true;
	return false;
}

void CheckWaveTransition(int WINDOW_WIDTH, int WINDOW_HEIGHT, sf::Clock& clock, int& waveTransition, Text& textWaveNumber, bool& endWave, float& waveTime, bool& drawWaveNumber, Earth& earth, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, std::vector<Boss>& gameBosses, std::vector<Egg>& eggs, int& wave_number, Wave& waveManager, ResourceLoader& resourceLoader, Time& waveStartTime)
{
	//
	float time = clock.getElapsedTime().asSeconds();
	std::string stWaveNumber = "Wave ";
	stWaveNumber += std::to_string(waveTransition);
	textWaveNumber.setString(stWaveNumber);
	textWaveNumber.setPosition(WINDOW_WIDTH / 2 - textWaveNumber.getLocalBounds().width / 2, WINDOW_HEIGHT / 3 - textWaveNumber.getLocalBounds().height / 3);
	//
	if (endWave == true)
	{
		if (time > waveTime)
		{
			drawWaveNumber = false;
			eggs.clear();
			earth.Reset();
			asteroids.clear();
			chickens.clear();
			gameBosses.clear();
			if (waveTransition % 10 == 1 || waveTransition % 10 == 2)
			{
				wave_number = 1;
				waveManager.Wave1Init(chickens, resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken), WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				waveManager.Wave1SetPosition(chickens, WINDOW_WIDTH, WINDOW_HEIGHT);
				endWave = false;
			}
			if (waveTransition % 10 == 3)
			{
				waveStartTime = clock.getElapsedTime();
				wave_number = 3;
				if (wave_number / 10 % 10 % 2 == 0)
					waveManager.Wave3Init(resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid), asteroids, waveTransition);
				else if (wave_number / 10 % 10 % 2 != 0)
					waveManager.Wave3Init(resourceLoader.GetTexture(ResourceLoader::TextureType::AsteroidFlame), asteroids, waveTransition);
				endWave = false;
			}
			if (waveTransition % 10 == 4 || waveTransition % 10 == 5)
			{
				if (earth.WaveHasStarted() == false && earth.FinishedMoving() == true)
				{
					earth.SetWaveHasStarted(true);
					waveManager.Wave4And5Init(chickens, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				}
				earth.SetPosition(sf::Vector2f(WINDOW_WIDTH / 2, 0));
				earth.SetTarget(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3));
				wave_number = 4;
				endWave = false;
			}
			if (waveTransition % 10 == 6)
			{
				waveStartTime = clock.getElapsedTime();
				if (wave_number / 10 % 10 % 2 != 0)
					waveManager.wave6Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid)
						, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				else if (wave_number / 10 % 10 % 2 == 0)
					waveManager.wave6Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::AsteroidFlame)
						, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				wave_number = 6;
				endWave = false;
			}
			if (waveTransition % 10 == 7)
			{
				waveManager.Wave7Init(chickens, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				wave_number = 7;
				endWave = false;
			}
			if (waveTransition % 10 == 8)
			{
				waveStartTime = clock.getElapsedTime();
				wave_number = 8;
				waveManager.Wave8Init(chickens, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				endWave = false;
			}
			if (waveTransition % 10 == 9)
			{
				waveStartTime = clock.getElapsedTime();
				wave_number = 9;
				if (wave_number / 10 % 10 % 2 != 0)
					waveManager.Wave9Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::Asteroid)
						, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				else if (wave_number / 10 % 10 % 2 == 0)
					waveManager.Wave9Init(asteroids, resourceLoader.GetTexture(ResourceLoader::TextureType::AsteroidFlame)
						, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				endWave = false;
			}
			if (waveTransition % 10 == 0 && waveTransition != 0)
			{
				wave_number = 10;
				waveManager.Wave10Init(gameBosses, resourceLoader, WINDOW_WIDTH, WINDOW_HEIGHT, waveTransition);
				endWave = false;
			}
		}
		else
			drawWaveNumber = true;
	}
	else if (chickens.empty() == true && asteroids.empty() == true && gameBosses.empty() == true)
	{
		if (wave_number != 4)
		{
			endWave = true;
			waveTransition++;
			waveTime = time + 5;
		}
		else if (earth.WaveHasStarted() == true)
		{
			endWave = true;
			waveTransition++;
			waveTime = time + 5;
		}
	}
}
void CheckInput(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int& wave_number, bool& start_game, bool& mainMenuLeaderboardSelected, Player& player, ResourceLoader& resourceLoader, int& Contor, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Asteroid>& asteroids, std::vector<Chicken>& chickens, Wave& waveManager, Earth& earth, bool& isPaused, PauseMenu& pauseMenu, int& pause_selected, std::vector<Boss>& gameBosses, bool& leaderboardIsActive, std::vector<Present>& presents, std::vector<Egg>& eggs, Clock& clock, bool& endGame, std::string& playerName, DataSaver& dataSaver, Leaderboard& leaderboard, bool& savePlayerData, int& waveTransition, bool& endWave, float& waveTime, std::vector<Feather>& feathers, Networking& net, char playMode, char connectionMode, bool& netCheckStartGame, AI_Companion& aiCompanion, uint32_t &scoreBeforeDeath)
{
	Event eventHandler;
	while (gameWindow.pollEvent(eventHandler))
	{
		if (savePlayerData == true && eventHandler.type == Event::TextEntered)
		{
			if (eventHandler.text.unicode == 8 && playerName.size() != 0)
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
					aiCompanion.SetMovement(false, 1);
				}
			}
			if (eventHandler.key.code == Keyboard::Right)
			{
				if (!isPaused)
				{
					player.SetMovement(true, 1);
					aiCompanion.SetMovement(true, 1);
				}
			}
			if (eventHandler.key.code == Keyboard::Space || eventHandler.key.code == Keyboard::Enter || eventHandler.key.code == Keyboard::Z)
			{
				if (start_game == false)
				{
					if (eventHandler.key.code == Keyboard::Space)
					{
						if (playMode == '1')
						{
							//if (connectionMode == 's')
							//{
							net.packet << "start game";
							net.SendData();
							net.packet.clear();

							/*std::cout << "start game";
							wave_number = 1;
							waveTransition = 1;
							start_game = true;*/
							//}

							/*std::string data;
							net.ReceiveData();
							net.packet >> data;
							*/

							netCheckStartGame = true;
						}
						else
						{
							wave_number = 1;
							waveTransition = 1;
							start_game = true;
						}
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
						ResetGame(clock, wave_number, chickens, asteroids, meat, gameBosses, gameMissiles, GameBullets, eggs, presents, Contor, player, start_game, isPaused, endGame, savePlayerData, waveTransition, endWave, waveTime, feathers, aiCompanion,scoreBeforeDeath);

					}
					if (pause_selected == 3)
						gameWindow.close();
				}
				if (savePlayerData == true && eventHandler.key.code == Keyboard::Enter)
				{
					/*if (playMode == '1')
					{
						net.packet << playerName << player.GetScore();
						net.SendData();

						std::string player2Name;
						uint32_t player2Score;

						net.ReceiveData();
						net.packet >> player2Name >> player2Score;
						dataSaver.SaveData(player2Name, player2Score);
					}*/

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
					if (endGame == true)					
						ResetGame(clock, wave_number, chickens, asteroids, meat, gameBosses, gameMissiles, GameBullets, eggs, presents, Contor, player, start_game, isPaused, endGame, savePlayerData, waveTransition, endWave, waveTime, feathers, aiCompanion, scoreBeforeDeath);
	
					
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
		}
		if (eventHandler.type == Event::KeyReleased)
		{
			if (eventHandler.key.code == Keyboard::Left)
			{
				player.SetMovement(false, 0);
				aiCompanion.SetMovement(false, 0);
			}
			if (eventHandler.key.code == Keyboard::Right)
			{
				player.SetMovement(true, 0);
				aiCompanion.SetMovement(true, 0);
			}
			if (eventHandler.key.code == Keyboard::Z)
			{
				if (!isPaused && player.IsDead() == false)
				{
					Bullet x(player.GetPosition().x, player.GetPosition().y, resourceLoader.GetTexture(ResourceLoader::TextureType::Bullet));
					for (int i = 0; i < Contor; i++)
					{
						x.Present_Collected();
					}
					GameBullets.emplace_back(std::move(x));
				}

			}
			if (eventHandler.key.code == Keyboard::X)
			{
				if (player.IsDead() == false && player.GetNrMissiles() > 0)
				{
					Missile missile(player.GetPosition().x, player.GetPosition().y, resourceLoader.GetTexture(ResourceLoader::TextureType::Rocket));
					gameMissiles.emplace_back(std::move(missile));
					player.ShootMissile();
				}
			}
			if (eventHandler.key.code == Keyboard::Num1)
			{
				asteroids.clear();
				chickens.clear();
				eggs.clear();
				waveTransition = 9;
			}
		}
	}
}void Movement(int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, Time& deltaTime, ScrollBackground& gameBackground, Player& player, std::vector<Egg>& eggs, std::vector<Chicken>& chickens, std::vector<Present>& presents, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, ResourceLoader& resourceLoader, Wave& waveManager, Earth& earth, bool& isPaused, PauseMenu& pauseMenu, RenderWindow& gameWindow, std::vector<Boss>& gameBosses, int& waveTransition, std::vector<Feather>& feathers, AI_Companion& aiCompanion,uint32_t &scoreBeforeDeath)
{
	gameBackground.AnimateBackground();
	player.MoveShip(WINDOW_WIDTH);
	aiCompanion.MoveShip(WINDOW_WIDTH, player.GetPosition(), player.GetSize());
	//Move each egg from the eggs vector
	if (!isPaused)
	{
		for (int index = 0; index < eggs.size(); index++)
			if (eggs[index].FallDown(WINDOW_HEIGHT) == false)
				eggs.erase(eggs.begin() + index);

		for (int index = 0; index < meat.size(); index++)
			if (meat[index].Move(WINDOW_WIDTH, WINDOW_HEIGHT, deltaTime.asSeconds()) == false)
				meat.erase(meat.begin() + index);
		for (int i = 0; i < feathers.size(); i++)
			if (feathers[i].Move(WINDOW_WIDTH, WINDOW_HEIGHT, deltaTime.asSeconds()) == false)
				feathers.erase(feathers.begin() + i);
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
			waveManager.Wave1Movement(chickens,player,aiCompanion,scoreBeforeDeath);
	}
	if (wave_number == 3)
	{
		if (!isPaused)
		{
			for (int index = 0; index < asteroids.size(); index++)
			{
				if (asteroids[index].Falldown(WINDOW_HEIGHT, asteroids[index].getasteroidsSpeed() - 10, asteroids[index].getasteroidsSpeed() - 10))
					asteroids.erase(asteroids.begin() + index);
			}
		}

	}
	if (wave_number == 4 || wave_number == 5)
	{
		if (!isPaused)
		{
			earth.Move();
			waveManager.Wave4And5Movement(chickens, WINDOW_WIDTH, WINDOW_HEIGHT,player,aiCompanion,scoreBeforeDeath);

		}	if (earth.WaveHasStarted() == true && chickens.size() == 0)
			earth.SetTarget(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT + earth.GetSize().y));

	}
	if (wave_number == 6)
	{
		if (!isPaused)
			waveManager.wave6Movement(asteroids, WINDOW_WIDTH, WINDOW_HEIGHT,player,aiCompanion,scoreBeforeDeath);

	}
	if (wave_number == 7)
	{
		if (!isPaused)
			waveManager.Wave7Movement(chickens, WINDOW_WIDTH, WINDOW_HEIGHT,player,aiCompanion,scoreBeforeDeath);
	}
	if (wave_number == 8)
	{
		if (!isPaused)
			waveManager.Wave8Movement(chickens, WINDOW_WIDTH, WINDOW_HEIGHT,player,aiCompanion,scoreBeforeDeath);
	}
	if (wave_number == 9)
	{
		if (!isPaused)
			waveManager.Wave9Movement(asteroids, WINDOW_WIDTH, WINDOW_HEIGHT,player,aiCompanion,scoreBeforeDeath);
	}
	if (wave_number == 10)
	{
		if (!isPaused)
			waveManager.Wave10Movement(gameBosses, WINDOW_WIDTH, WINDOW_HEIGHT,player,aiCompanion,scoreBeforeDeath);
	}

	if (!isPaused)
		for (int i = 0; i < presents.size(); i++)
			presents[i].FallDownPresent(WINDOW_HEIGHT);
}

void CheckCollisions(Clock& clock, ResourceLoader& resourceLoader, Player& player, int& Contor, std::vector<Egg>& eggs, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, std::vector<Chicken>& chickens, std::vector<Present>& presents, bool& isPaused, std::vector<Boss>& gameBosses, int wave_number, const Time& waveStartTime, std::vector<Feather>& feathers, uint32_t &scoreBeforeDeath, AI_Companion& aiCompanion)
{
	if (player.IsDead() == false)
	{
		//Check if any of the eggs collides with the ship
		for (int index = 0; index < eggs.size(); index++)
			if (CheckSpriteCollision(player.GetSprite().getGlobalBounds(), eggs[index].GetSprite().getGlobalBounds()))
			{
				if (player.IsImmortal() == false)
				{
					//If so erase the egg and kill the player
					eggs.erase(eggs.begin() + index);

					explosions.push_back(Explosion());
					explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
					explosions[explosions.size() - 1].explosion_setPosition(player.GetPosition().x, player.GetPosition().y);
					player.Die();
					scoreBeforeDeath = player.GetScore();
					aiCompanion.SetInactive();
					aiCompanion.ChangeActivatedValue();
					if (Contor >= 1)
						Contor--;
				}
			}
		//check if the asteroids colide with ship 
		for (int index = 0; index < asteroids.size(); index++)
		{
			FloatRect asteroidCollider = asteroids[index].GetSprite().getGlobalBounds();
			float rotation = asteroids[index].GetSprite().getRotation();
			if (rotation > 270 && rotation < 340)
				asteroidCollider.left += asteroidCollider.width * 2.0 / 3;
			if (rotation >= 40 && rotation < 90)
				asteroidCollider.left += 25;
			if (rotation != 0)
				asteroidCollider.top += asteroidCollider.height * 2.0 / 3;
			else
				asteroidCollider.top += asteroidCollider.height * 3.0 / 4;
			asteroidCollider.height *= 1.0 / 3;
			if (rotation != 0)
				asteroidCollider.width *= 1.0 / 3;

			asteroidCollider.height *= 2.0 / 3;
			asteroidCollider.width *= 2.0 / 3;


			if (CheckSpriteCollision(player.GetSprite().getGlobalBounds(), asteroidCollider) && clock.getElapsedTime().asSeconds() - waveStartTime.asSeconds() > 0.1f)
			{
				if (player.IsImmortal() == false)
				{
					//If so erase the asteroid and kill the player
					asteroids.erase(asteroids.begin() + index);

					explosions.push_back(Explosion());
					explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
					explosions[explosions.size() - 1].explosion_setPosition(player.GetPosition().x, player.GetPosition().y);

					player.Die();
					scoreBeforeDeath = player.GetScore();
					aiCompanion.SetInactive();
					aiCompanion.ChangeActivatedValue();
					if (Contor > 1)
						Contor--;
				}
			}
		}
		//check if the meat and present collides with the ship
		for (int index = 0; index < meat.size(); index++)
			if (CheckSpriteCollision(player.GetSprite().getGlobalBounds(), meat[index].GetSprite().getGlobalBounds()))
			{
				player.UpdateScore(meat[index].getMeatScore());
				meat.erase(meat.begin() + index);
				player.AddMeat();
			}
		for (int i = 0; i < presents.size(); i++)
			if (CheckSpriteCollision(player.GetSprite().getGlobalBounds(), presents[i].GetSprite().getGlobalBounds()))
			{
				presents.erase(presents.begin() + i);
				Contor++;
			}

		if (wave_number % 7 == 0 || wave_number % 8 == 0 && clock.getElapsedTime().asSeconds() - waveStartTime.asSeconds() > 0.1f)
		{
			for (int index = 0; index < chickens.size(); index++)
			{
				if (player.IsImmortal() == false)
				{
					if (CheckSpriteCollision(player.GetSprite().getGlobalBounds(), chickens[index].GetSprite().getGlobalBounds()))
					{
						chickens.erase(chickens.begin() + index);

						//Player explosion
						explosions.push_back(Explosion());
						explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
						explosions[explosions.size() - 1].explosion_setPosition(player.GetPosition().x, player.GetPosition().y);
						player.Die();
						scoreBeforeDeath = player.GetScore();
						aiCompanion.SetInactive();
						aiCompanion.ChangeActivatedValue();
						if (Contor > 1)
							Contor--;
					}
				}
			}
		}
	}
	//check if bullets collides with asteroids
	for (int index = 0; index < asteroids.size(); index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for (int z = 0; z < 7; z++)
				if (GameBullets[j].GetState(z) == true)
				{
					FloatRect asteroidCollider = asteroids[index].GetSprite().getGlobalBounds();
					float rotation = asteroids[index].GetSprite().getRotation();
					if (rotation > 270 && rotation < 340)
						asteroidCollider.left += asteroidCollider.width * 2.0 / 3;
					if (rotation >= 40 && rotation < 90)
						asteroidCollider.left += 25;
					if (rotation != 0)
						asteroidCollider.top += asteroidCollider.height * 2.0 / 3;
					else
						asteroidCollider.top += asteroidCollider.height * 3.0 / 4;
					asteroidCollider.height *= 1.0 / 3;
					if (rotation != 0)
						asteroidCollider.width *= 1.0 / 3;

					asteroidCollider.height *= 2.0 / 3;
					asteroidCollider.width *= 2.0 / 3;

					if (CheckSpriteCollision(GameBullets[j].GetSprite(z).getGlobalBounds(), asteroidCollider))
					{
						if (asteroids[index].GetLife() == 1)
						{
							player.UpdateScore(asteroids[index].getScore());
							explosions.push_back(Explosion());
							explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
							explosions[explosions.size() - 1].explosion_setScale(0.25 * asteroids[index].getScale() * 10, 0.25 * asteroids[index].getScale() * 10);
							explosions[explosions.size() - 1].explosion_setPosition(asteroids[index].GetPosition().x, asteroids[index].GetPosition().y);
							asteroids.erase(asteroids.begin() + index);
						}
						else
							asteroids[index].GetHit();
						GameBullets[j].SetStateFalse(z);
						z = 7;
						j = GameBullets.size();
					}
				}
	//IsOnTheScreen
	for (int i = 0; i < asteroids.size(); i++)
		if (asteroids[i].IsOnTheScreen() == false)
			asteroids.erase(asteroids.begin() + i);
	for (int i = 0; i < chickens.size(); i++)
		if (chickens[i].IsOnTheScreen() == false)
			chickens.erase(chickens.begin() + i);
	//check if bullets collides with chickens
	for (int index = 0; index < chickens.size(); index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for (int z = 0; z < 7; z++)
				if (GameBullets[j].GetState(z) == true)
					if (CheckSpriteCollision(GameBullets[j].GetSprite(z).getGlobalBounds(), chickens[index].GetSprite().getGlobalBounds()))
					{

						if (chickens[index].GetLife() == 1)
						{
							player.UpdateScore(chickens[index].getChickenScore());
							explosions.push_back(Explosion());
							explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
							explosions[explosions.size() - 1].explosion_setPosition(chickens[index].getPosition().x, chickens[index].getPosition().y - 20);
							Meat meatClone(sf::Vector2f(chickens[index].getPosition().x - 10, chickens[index].getPosition().y - 20), resourceLoader.GetTexture(ResourceLoader::TextureType::Meat));
							meat.push_back(std::move(meatClone));
							int random = rand() % 30;
							if (random == 3)
							{
								Present presentClone(sf::Vector2f(chickens[index].getPosition().x - 10, chickens[index].getPosition().y - 20), resourceLoader.GetTexture(ResourceLoader::TextureType::Gift));
								presents.push_back(std::move(presentClone));
							}
							chickens.erase(chickens.begin() + index);
						}
						else
							chickens[index].GetHit();
						GameBullets[j].SetStateFalse(z);
						z = 7;
						j = GameBullets.size();
					}

	for (int index = 0; index < gameBosses.size(); index++)
		for (int j = 0; j < GameBullets.size(); j++)
			for (int z = 0; z < 7; z++)
				if (GameBullets[j].GetState(z) == true)
					if (CheckSpriteCollision(GameBullets[j].GetSprite(z).getGlobalBounds(), gameBosses[index].GetSprite().getGlobalBounds()))
					{
						for (int a = 0; a < 2; a++)
						{
							Feather featherCl(sf::Vector2f(gameBosses[index].GetPosition().x + 200, gameBosses[index].GetPosition().y + 300), resourceLoader.GetTexture(ResourceLoader::TextureType::Feather));
							feathers.emplace_back(std::move(featherCl));
						}
						player.UpdateScore(gameBosses[index].GetScore());
						if (gameBosses[index].GetLife() == 1)
						{
							player.UpdateScore(gameBosses[index].GetScore() * 10);
							explosions.push_back(Explosion());
							explosions[explosions.size() - 1].setSprite_explosion(resourceLoader.GetTexture(ResourceLoader::TextureType::Explosion));
							explosions[explosions.size() - 1].explosion_setPosition(gameBosses[index].GetPosition().x - 200, gameBosses[index].GetPosition().y - 100);
							explosions[explosions.size() - 1].explosion_setScale(3, 3);
							for (int a = 0; a < 30; a++)
							{
								Meat meatClone(sf::Vector2f(gameBosses[index].GetPosition().x + 200, gameBosses[index].GetPosition().y + 300), resourceLoader.GetTexture(ResourceLoader::TextureType::Meat));
								meat.emplace_back(std::move(meatClone));

							}
							for (int a = 0; a < 30; a++)
							{
								Feather featherCl(sf::Vector2f(gameBosses[index].GetPosition().x + 200, gameBosses[index].GetPosition().y + 300), resourceLoader.GetTexture(ResourceLoader::TextureType::Feather));
								feathers.emplace_back(std::move(featherCl));
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

	uint32_t currentScore=player.GetScore();


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
			int randomPoz = std::rand() % 200 + 100;
			int random = std::rand() % 10;
			if (random == 4)
			{

				Egg clone(sf::Vector2f(gameBosses[i].GetPosition().x + randomPoz, gameBosses[i].GetPosition().y + 500), resourceLoader.GetTexture(ResourceLoader::TextureType::Egg));
				eggs.push_back(std::move(clone));
			}

		}
	}
}

void DrawEverything(RenderWindow& gameWindow, int WINDOW_WIDTH, int WINDOW_HEIGHT, int wave_number, ResourceLoader& resourceLoader, TitleScreen& titleScreen, ScrollBackground& gameBackground, Player& player, std::vector<Present>& presents, std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Bullet>& GameBullets, std::vector<Egg>& eggs, bool& selected, bool& start_game, const Time& deltaTime, std::vector<Explosion>& explosions, std::vector<Meat>& meat, std::vector<Missile>& gameMissiles, Earth& earth, PauseMenu& pauseMenu, bool& isPaused, int& pause_selected, std::vector<Boss>& gameBosses, bool leaderboardIsActive, Leaderboard& leaderboardPanel, bool endGame, Text gameOverText, std::string& playerName, bool& drawWaveNumber, Text textWaveNumber, std::vector<Feather>& feathers, AI_Companion& aiCompanion)
{
	gameWindow.clear();
	if (wave_number == 0)
	{
		titleScreen.IntroMain_Display(gameWindow, titleScreen);
		drawWaveNumber = false;
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
		aiCompanion.Animate();
		aiCompanion.DrawShip(gameWindow);
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
		for (int i = 0; i < feathers.size(); i++)
			feathers[i].Draw(gameWindow);

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
	if (drawWaveNumber == true)
		gameWindow.draw(textWaveNumber);
	if (leaderboardIsActive)
		leaderboardPanel.Draw(gameWindow);

	gameWindow.display();
}
