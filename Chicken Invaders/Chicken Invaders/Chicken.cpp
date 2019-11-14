#include "Chicken.h"

void Chicken::Animation()
{
	frame += animSpeed;
	if (frame > frameCount) frame = 0;
	sprite_chicken.setTextureRect(IntRect(int(frame) * 256, 0, 256, 256));
	
}
