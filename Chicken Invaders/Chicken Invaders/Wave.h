#pragma once
#include"Chicken.h"
#include "Asteroid.h"
#include"Explosion.h"
class Wave
{
public:
	Chicken chicken[5][8];
	bool left_or_right_movement = true;
	//this is the first wave where we have 5 x 6 chickens
	void fisrtWavePosition(Chicken chicken[5][8], const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
	void drawWave(RenderWindow& map,Chicken chicken[5][8]);
	void setSprite(Texture& enemy,Chicken chicken[5][8]);
	void movementFirstWave(Chicken chicken[5][8]);


	

	

};

