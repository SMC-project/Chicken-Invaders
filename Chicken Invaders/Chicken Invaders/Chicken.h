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
	float frame = 0;
	float animSpeed = 0.05;
	int frameCount = 45;
public:
	void Animation();
private:
	Sprite mSpriteChicken;
	Texture mTextureChicken;
};

