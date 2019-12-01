#include "Explosion.h"

bool Explosion::explosion()
{
	frame_explosion += animSpeed_explosion;
	if (frame_explosion > frameCount_explosion)
		return false;
	sprite_explosion.setTextureRect(IntRect(int(frame_explosion) * 256, 0, 256, 256));
	return true;
}

void Explosion::setSprite_explosion(const Texture& texture)
{
	sprite_explosion.setTexture(texture);
	sprite_explosion.setScale(.5, .5);
}

bool Explosion::draw_explosion(RenderWindow& map)
{
	if (explosion() == false)
		return false;
	map.draw(sprite_explosion);
	return true;
}

void Explosion::explosion_setPosition(float x_POS, float y_POS)
{
	sprite_explosion.setPosition(x_POS, y_POS);
}
