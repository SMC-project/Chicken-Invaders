#pragma once
#include "enemy.h"
#include<SFML/Graphics.hpp>
#include<iostream>

#include<time.h>

using namespace sf;
class Chicken :
	public enemy
{

public:
	Chicken();
	
	Sprite sprite_chicken;
	Sprite sprite_explosion;

	Sprite sprite_asteroid;


	float animSpeed = 0.03;
	float frame = 0;
	int frameCount = 45;
	float frame_explosion = 0;


	int frameCount_explosion = 45;



	float animSpeed_explosion = 1;

public:
	void Animation();
	void explosion();




};

