#include "Explosion.h"

void Explosion::explosion()
{
	frame_explosion += animSpeed_explosion;
	if (frame_explosion > frameCount_explosion) frame_explosion = 0;
	sprite_explosion.setTextureRect(IntRect(int(frame_explosion) * 256, 0, 256, 256));
}

void Explosion::setSprite_explosion(Texture& explosion, Explosion& chicken_explode)
{
	explosion.loadFromFile("Sprites/Extras/type_C.png");
	chicken_explode.sprite_explosion.setTexture(explosion);
	chicken_explode.sprite_explosion.setScale(.5, .5);
}

void Explosion::draw_explosion(RenderWindow& map, Explosion& explode)
{
	explode.explosion();
	map.draw(explode.sprite_explosion);

}

void Explosion::explosion_setPosition(Explosion& object, float x_POS, float y_POS)
{
	object.sprite_explosion.setPosition(x_POS, y_POS);
}
