#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<time.h>

using namespace sf;
class Chicken
{

public:
	Chicken();
	Sprite sprite_chicken;

private:
	//those are for chicken
	float frame = 0;
	float animSpeed = 0.03;
	int frameCount = 45;

public:
	void Animation();
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

