#include <iostream>
#include <Windows.h>
#include "Map.h"

void GameLoop();
void CheckForInput(Map& myMap, std::pair<int, int> newPlayerPos, std::pair<int, int>& playerPos);

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
		
		//Sleep(500);
	}
}

void CheckForInput(Map& myMap, std::pair<int, int> newPlayerPos, std::pair<int, int>& playerPos)
{
	if (GetAsyncKeyState(VK_DOWN))
	{
		newPlayerPos = playerPos;
		newPlayerPos.first++;

		myMap.MoveChar(playerPos, newPlayerPos, '@');
		playerPos = newPlayerPos;
		myMap.Redraw();
	}
}