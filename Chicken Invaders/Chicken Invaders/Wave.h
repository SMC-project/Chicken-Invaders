#pragma once
#include"Chicken.h"
#include "Asteroid.h"
#include"Explosion.h"
#include "Present.h"
#include<time.h>

class Wave
{
private:
	//used in the first wave changing the state of direction
	bool left_or_right_movement = true;
	//used to get random initial position
	int random_number;



public:
	int wave_number = 0;

#pragma region Wave1

	//this is the first wave where we have 5 x 6 chickens
	void fisrtWavePosition(Chicken chicken[5][8], const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
	void drawWave(RenderWindow& map,Chicken chicken[5][8]);
	void setSprite(Texture& enemy,Chicken chicken[5][8]);
	void movementFirstWave(Chicken chicken[5][8]);

#pragma endregion

#pragma region Wave3

	void drawWave_asteroid(RenderWindow& map, Asteroid asteroidVect[5][5]);
	void setSprite_asteroid1(Texture& asteroid, Asteroid asteroidVect[5][5]);
	void thirdWave_Position(Asteroid asteroidVect[5][5]);
	void thirdWave_Movement(Asteroid asteroidVect[5][5]);

#pragma endregion



};

