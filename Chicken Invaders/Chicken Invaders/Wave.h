#pragma once
#include"Chicken.h"
#include "Asteroid.h"
#include"Explosion.h"
#include "Present.h"
#include<time.h>
#include"ResourceLoader.h"

class Wave
{
public:
	void Init_asteroids(std::vector<Asteroid>& asteroids,ResourceLoader resource);
};

