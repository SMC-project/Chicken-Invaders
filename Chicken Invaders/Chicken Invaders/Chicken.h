#pragma once
#include "enemy.h"
#include"Map.h"
#include<time.h>
class Chicken :
	public enemy
{
	void isShooting(Map& mymap, Chicken current_chicken);
	bool Drop_Present(Map& mymap, Chicken current_chicken);
	void isDropingPresent(Map& mymap, Chicken current_chicken);
	bool Drop_food();
	void isDropingFood(Map& mymap, Chicken current_chicken);
	bool Drop_egg();
	enum type {
		horzizontal,
		zigzag,
		circle,
	};
};

