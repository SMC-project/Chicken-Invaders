#pragma once
#include "Map.h"
class enemy
{
public:
	std::pair<int, int> m_previousPos;
	std::pair<int, int> m_newPos;
	char m_c;

public:
	enemy(std::pair<int, int> newPos, char c,Map& mymap);
	void movement(Map& mymap)
	{
		mymap.MoveChar(m_previousPos,m_newPos,m_c);
	}
};

