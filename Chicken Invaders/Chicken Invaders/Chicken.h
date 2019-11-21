#pragma once
#include "enemy.h"
#include<SFML/Graphics.hpp>

#include<time.h>

using namespace sf;
class Chicken :
	public enemy
{

public:
	Chicken();
	
	Sprite sprite_chicken;
	Sprite sprite_explosion;
	Sprite setDropPresent;

	float frame = 0;

	float animSpeed = 0.03;


	int frameCount = 45;
	float framePresent = 0;
	float frame_explosion = 0;

	int frameCount_explosion = 45;
	int frameCountPresent = 45;

	float animeSpeedPresent = 1;
	float animSpeed_explosion = 1;
public:
	void Animation();
	void explosion();
	void dropPresent();


};

