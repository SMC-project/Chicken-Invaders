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
	void explosion();
	//these are the functions that are setting the explosion when an enemy dies
	void setSprite_explosion(Texture& explosion, Explosion& chicken_explode);
	void draw_explosion(RenderWindow& map, Explosion& explode);
	void explosion_setPosition(Explosion& object, float x_POS, float y_POS);
};

