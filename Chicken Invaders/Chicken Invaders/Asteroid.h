#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<time.h>
using namespace sf;
class Asteroid
{
private:
	
	float frame_asteroid1 = 0;
	int framecount_asteroid1 = 29;
	float animSpeed_Asteroid1 = .2;

public:
	Sprite sprite_asteroid;
	void Asteroid_animation();

	//functions of the asteroids
	void setSprite_asteroid(Texture& asteroid, Asteroid& asteroid_object);
	void draw_asteroid(RenderWindow& map, Asteroid& asteroid_object);
	void asteroid_setPosition(Asteroid& asteroid_object, float x_POS, float y_POS);
};

