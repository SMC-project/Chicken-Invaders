#include <iostream>
#include <Windows.h>
#include "Map.h"

void GameLoop();
void CheckForInput(Map& myMap, std::pair<int, int> newPlayerPos, std::pair<int, int>& playerPos);
bool CollisionCheck(const Map& myMap, std::pair<int, int> newPos);

int main()
{
	GameLoop();
	system("pause");
}

void GameLoop()
{
	std::pair<int, int> newPlayerPos;
	std::pair<int, int> playerPos(1, 2);
	bool stopGame = false;
	Map myMap;
	myMap.Redraw();

	while (stopGame == false)
	{
		CheckForInput(myMap, newPlayerPos, playerPos);
		//Sleep(500);
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