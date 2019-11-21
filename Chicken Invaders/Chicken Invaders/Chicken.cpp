#include "Chicken.h"
using namespace sf;
Chicken::Chicken()
{
}



void Chicken::Animation()
{
	frame += animSpeed;
	if (frame > frameCount) frame = 0;
	sprite_chicken.setTextureRect(IntRect(int(frame) * 256, 0, 256, 256));
	
}

void Chicken::explosion()
{
	frame_explosion += animSpeed_explosion;
	if (frame_explosion > frameCount_explosion) frame_explosion = 0;
	sprite_explosion.setTextureRect(IntRect(int(frame_explosion) * 256, 0, 256, 256));
}



void Chicken::dropPresent()
{
	framePresent += animeSpeedPresent;
	if (framePresent > frameCountPresent) framePresent = 0;
	setDropPresent.setTextureRect(IntRect(int(framePresent) * 256, 0, 256, 256));

}



