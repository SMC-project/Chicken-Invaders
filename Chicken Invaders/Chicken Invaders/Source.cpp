#include <iostream>
#include<SFML/Graphics.hpp>
#include"Map.h"
#include<Windows.h>


void GameLoop(sf::RenderWindow& gameWindow);
void CheckForInput(Map& myMap, std::pair<int, int> newPlayerPos, std::pair<int, int>& playerPos);
bool CollisionCheck(const Map& myMap, std::pair<int, int> newPos);

int main()
{

	sf::RenderWindow gameWindow(sf::VideoMode(800, 800), "gameWindow", sf::Style::Close | sf::Style::Resize);
	gameWindow.setFramerateLimit(30);

	GameLoop(gameWindow);
	return 0;


}


void GameLoop(sf::RenderWindow& gameWindow)
{
	sf::Texture myTexture;
	myTexture.loadFromFile("Sprites/Weapons/bullet.png");
	sf::Sprite mySprite(myTexture);
	mySprite.setPosition(20, 20);
	mySprite.setScale(.2, .23);
	while (gameWindow.isOpen())
	{
		sf::Event eventHandler;
		while (gameWindow.pollEvent(eventHandler))
		{
			if (eventHandler.type == sf::Event::Closed)
				gameWindow.close();
		}
		gameWindow.clear();

		//Here is where we draw stuff;
		gameWindow.draw(mySprite);

		gameWindow.display();

	}
}

void CheckForInput(Map& myMap, std::pair<int, int> newPlayerPos, std::pair<int, int>& playerPos)
{
	if (GetAsyncKeyState(VK_UP))
	{
		newPlayerPos = playerPos;
		newPlayerPos.first--;
		if (CollisionCheck(myMap, newPlayerPos) == false)
			return;

		myMap.MoveChar(playerPos, newPlayerPos, '@');
		playerPos = newPlayerPos;
		myMap.Redraw();
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		newPlayerPos = playerPos;
		newPlayerPos.first++;
		if (CollisionCheck(myMap, newPlayerPos) == false)
			return;

		myMap.MoveChar(playerPos, newPlayerPos, '@');
		playerPos = newPlayerPos;
		myMap.Redraw();
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		newPlayerPos = playerPos;
		newPlayerPos.second--;
		if (CollisionCheck(myMap, newPlayerPos) == false)
			return;

		myMap.MoveChar(playerPos, newPlayerPos, '@');
		playerPos = newPlayerPos;
		myMap.Redraw();
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		newPlayerPos = playerPos;
		newPlayerPos.second++;
		if (CollisionCheck(myMap, newPlayerPos) == false)
			return;

		myMap.MoveChar(playerPos, newPlayerPos, '@');
		playerPos = newPlayerPos;
		myMap.Redraw();
	}
}

//Returns true if it can move to that position
bool CollisionCheck(const Map& myMap, std::pair<int, int> newPos)
{
	if (myMap.map[newPos.first][newPos.second] == ' ')
		return true;
	return false;
}