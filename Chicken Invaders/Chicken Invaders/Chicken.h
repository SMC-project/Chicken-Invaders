#pragma once
#include "enemy.h"

#include<time.h>
class Chicken :
	public enemy
{
	void isShooting(Chicken current_chicken);
	bool Drop_Present( Chicken current_chicken);
	void isDropingPresent( Chicken current_chicken);
	bool Drop_food();
	void isDropingFood(Chicken current_chicken);
	bool Drop_egg();
	enum type {
		horzizontal,
		zigzag,
		circle,
	};
};

