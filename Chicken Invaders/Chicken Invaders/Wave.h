#pragma once
#include"Chicken.h"
class Wave
{
public:
	Chicken chicken[5][8];
	bool left_or_right_movement = true;
	void fisrtWavePosition(Chicken chicken[5][8]);
	void drawWave(RenderWindow& map,Chicken chicken[5][8]);
	void setSprite(Texture& enemy,Chicken chicken[5][8]);
	void movementFirstWave(Chicken chicken[5][8]);
};

