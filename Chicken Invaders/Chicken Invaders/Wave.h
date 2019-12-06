#pragma once
#include"Chicken.h"
#include "Asteroid.h"
#include"Explosion.h"
#include "Present.h"
#include<time.h>
#include "ResourceLoader.h"

class Wave
{
private:
	//used in the first wave changing the state of direction
	bool left_or_right_movement = true;
	//used to get random initial position
	int random_number;



public:
	Wave();
	bool m_leftOrRightMovement = true;
	std::vector<Chicken> chickens;
	ResourceLoader resurceLoader;
	void firstWave(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int Window_width, int Window_height);
	void setPositionWaveOne(std::vector<Chicken>& chickens, int Window_width, int Window_height);
	void firstWaveMovement(std::vector<Chicken>& chickens, RenderWindow& map);

};

