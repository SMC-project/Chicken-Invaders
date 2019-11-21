#pragma once
#include"Chicken.h"
#include "Asteroid.h"
class Wave
{
public:
	Chicken chicken[5][8];
	bool left_or_right_movement = true;
	void fisrtWavePosition(Chicken chicken[5][8], const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
	void drawWave(RenderWindow& map,Chicken chicken[5][8]);
	void setSprite(Texture& enemy,Chicken chicken[5][8]);
	void movementFirstWave(Chicken chicken[5][8], Chicken explosion);

	void setSprite_explosion(Texture& explosion,Chicken& chicken_explode);
	void draw_explosion(RenderWindow& map, Chicken& explode);
	void explosion_setPosition(Chicken& object,float x_POS,float y_POS);

	void setSprite_asteroid(Texture& asteroid,Asteroid& asteroid_object);
	void draw_asteroid(RenderWindow& map, Asteroid& asteroid_object);
	void asteroid_setPosition(Asteroid& asteroid_object, float x_POS, float y_POS);
};

