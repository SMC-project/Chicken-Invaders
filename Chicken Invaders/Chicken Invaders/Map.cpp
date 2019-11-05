#include "Map.h"

void Map::Redraw()
{
	system("cls");

	for (int index = 0; index < map.size(); index++)
	{
		std::cout << map[index] << "\n";
	}
}

bool Map::MoveChar(std::pair<int, int> previousPos, std::pair<int, int> newPos, char chToDraw)
{
	if (map[previousPos.first][previousPos.second] != chToDraw)
		return false;

	map[previousPos.first][previousPos.second] = ' ';
	map[newPos.first][newPos.second] = chToDraw;
	return true;
}