#include <iostream>
#include <Windows.h>
#include "Map.h"

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