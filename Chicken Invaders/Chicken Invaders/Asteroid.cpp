#include "Asteroid.h"


void Asteroid::Asteroid_animation()
{
	frame_asteroid += animSpeed_Asteroid;
	if (frame_asteroid > framecount_asteroid) frame_asteroid = 0;
	sprite_asteroid.setTextureRect(IntRect(int(frame_asteroid) * 256, 0, 256, 1024));
}
