#include "Explosion.h"

void Explosion::explosion()
{
	frame_explosion += animSpeed_explosion;
	if (frame_explosion > frameCount_explosion) frame_explosion = 0;
	sprite_explosion.setTextureRect(IntRect(int(frame_explosion) * 256, 0, 256, 256));
}

void Explosion::setSprite_explosion(const Texture& texture)
{
	sprite_explosion.setTexture(texture);
	sprite_explosion.setScale(.5, .5);
}

void Explosion::draw_explosion(RenderWindow& map)
{
	explosion();
	map.draw(sprite_explosion);
}

void Explosion::explosion_setPosition(float x_POS, float y_POS)
{
	sprite_explosion.setPosition(x_POS, y_POS);
}
