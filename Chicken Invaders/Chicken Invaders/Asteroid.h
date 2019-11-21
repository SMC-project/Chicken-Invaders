#pragma once
#include<SFML/Graphics.hpp>
#include<time.h>
using namespace sf;
class Asteroid
{
public:
	
	Sprite sprite_asteroid;
	float frame_asteroid1 = 0;
	int framecount_asteroid1 = 29;
	float animSpeed_Asteroid1 = 1;




public:
	void Asteroid_animation();
};

