#pragma once
#include<SFML/Graphics.hpp>
#include<time.h>
#include "Chicken.h"

using namespace sf;

class Present
{
public:
	float mCoordX;
	float mCoordY;
	Texture presentTexture;
	Present(int coordX, int xoordY);

	Sprite presentSprite;

	float framePresent = 0;
	int frameCountPresent = 39;
	float animeSpeedPresent = 1;

public:
	
	void setSpritePresent(Texture& presentTexture, Present& chickenPresent);
	void drawPresent(RenderWindow& map, Present& chickenPresent);
	void setPosition(Present& chickenPresent);
	void spawnPresent();
	void movePresent(Present& chickenPresent);



};

