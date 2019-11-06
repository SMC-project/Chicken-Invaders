#include "enemy.h"

enemy::enemy(std::pair<int, int> newPos, char c,Map& mymap)
{
	m_newPos = newPos;
	m_c = c;

	mymap.place(*this);
}
