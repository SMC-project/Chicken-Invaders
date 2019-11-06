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

void Map::place(enemy current_enemy)
{
	map[current_enemy.m_newPos.first][current_enemy.m_newPos.second] = current_enemy.m_c;
}
