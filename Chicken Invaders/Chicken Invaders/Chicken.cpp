#include "Chicken.h"

void Chicken::isShooting(Map& mymap,Chicken current_chicken)
{
	//if(current_chicken.Drop_egg)
		//mymap.map[current_chicken.m_newPos.first + 1][current_chicken.m_newPos.second] = 'o';
	
}

bool Chicken::Drop_Present(Map& mymap, Chicken current_chicken)
{
	srand(time(NULL));
	int drop = rand() % 100 + 1;
	if (drop < 21)
	{
		return true;
	}
	return false;
}

void Chicken::isDropingPresent(Map& mymap, Chicken current_chicken)
{
	//if (current_chicken.Drop_Present)
		//mymap.map[current_chicken.m_newPos.first + 1][current_chicken.m_newPos.second] = '$';
}

bool Chicken::Drop_food()
{
	srand(time(NULL));
	int drop = rand() % 100 + 1;
	if (drop < 41)
	{
		return true;
	}
	return false;
}

void Chicken::isDropingFood(Map& mymap, Chicken current_chicken)
{
	//if (current_chicken.Drop_food)
		//mymap.map[current_chicken.m_newPos.first + 1][current_chicken.m_newPos.second] = '&';
}

bool Chicken::Drop_egg()
{
	srand(time(NULL));
	int drop = rand() % 100 + 1;
	if (drop < 41)
	{
		return true;
	}
	return false;
}
