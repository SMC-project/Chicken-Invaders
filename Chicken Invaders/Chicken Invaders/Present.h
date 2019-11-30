#pragma once
#include<SFML/Graphics.hpp>

#include<iostream>
#include<time.h>

using namespace sf;
class Present
{
private:
	Sprite setDropPresent;
	float framePresent = 0;
	int frameCountPresent = 45;
	float animSpeed_Present = .8;
	float fallDownSpeed = 10;

public:
	void dropPresent();
	//functions of presents
	void setSpritePresent(const Texture& texture);
	void drawPresent(RenderWindow& map);
	void setPositionPresent(float posX, float posY);
	bool fallDownPresent(int windowHeight);

};
