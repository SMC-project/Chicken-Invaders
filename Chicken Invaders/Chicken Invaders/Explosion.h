#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<time.h>

using namespace sf;
class Explosion
{
private:
	Sprite sprite_explosion;
	float frame_explosion = 0;
	int frameCount_explosion = 45;
	float animSpeed_explosion = 1;

public:
	bool explosion();
	//these are the functions that are setting the explosion when an enemy dies
	void setSprite_explosion(const Texture& texture);
	bool draw_explosion(RenderWindow& map);
	void explosion_setPosition(float x_POS, float y_POS);
	void explosion_setScale(float width, float height);
};

