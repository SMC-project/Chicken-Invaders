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

	const int pi = 3.14159265359;
	int wave4and5NrChickens = 20;
	float radius1 = 600;
	float radius2 = 300;
	float degrees = 0;


public:
	Wave();
	bool m_leftOrRightMovement = true;
	std::vector<Chicken> chickens;
	ResourceLoader resurceLoader;
	void firstWave(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int Window_width, int Window_height);
	void setPositionWaveOne(std::vector<Chicken>& chickens, int Window_width, int Window_height);
	void firstWaveMovement(std::vector<Chicken>& chickens);

	void Wave4And5Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void Wave4And5Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT);
};

