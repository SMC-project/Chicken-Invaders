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
	float animSpeed = 0.01;
	int frameCount = 45;


public:
	void Animation();
};

