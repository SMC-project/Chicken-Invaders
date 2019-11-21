#include "Asteroid.h"


void Asteroid::Asteroid_animation()
{
	frame_asteroid1 += animSpeed_Asteroid1;
	if (frame_asteroid1 > framecount_asteroid1) frame_asteroid1 = 0;
	sprite_asteroid.setTextureRect(IntRect(int(frame_asteroid1) * 256, 0, 256, 1024));
}
