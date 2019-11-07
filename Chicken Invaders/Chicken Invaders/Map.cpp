#include "Map.h"



void Map::Redraw()
{
	system("cls");

	for (int index = 0; index < map.size(); index++)
	{
		std::cout << map[index] << "\n";
	}
}

void Map::placeObject(enemy& newEnemy)
{
	map[newEnemy.m_newPos.first][newEnemy.m_newPos.second] = newEnemy.m_c;
}

bool Map::MoveChar(std::pair<int, int> previousPos, std::pair<int, int> newPos, char chToDraw)
{
	if (map[previousPos.first][previousPos.second] != chToDraw)
		return false;

	map[previousPos.first][previousPos.second] = ' ';
	map[newPos.first][newPos.second] = chToDraw;
	return true;
}

void Map::MoveEnemy(enemy& newEnemy, std::pair<int, int> startPos, std::pair<int, int> endPos, char chToDraw)
{
	bool right = true;
	std::pair<int, int> currentPos=startPos;
	std::pair<int, int> previousPos;
	while (1)
	{
		if (right == true)
			if (currentPos.second != endPos.second)
				right = false;
			else {
				currentPos.second++;
				Map::Redraw();
			}
		if (right == false)
			if (currentPos.second != startPos.second)
				right = true;
			else {
				currentPos.second--;
				Map::Redraw();
			}
	}
	
}




