#include "Asteroid.h"


void Asteroid::Asteroid_animation()
{
	frame_asteroid1 += animSpeed_Asteroid1;
	if (frame_asteroid1 > framecount_asteroid1) frame_asteroid1 = 0;
	sprite_asteroid.setTextureRect(IntRect(int(frame_asteroid1) * 256, 0, 256, 1024));
}

void Asteroid::setSprite_asteroid(Texture& asteroid, Asteroid& asteroid_object)
{
	asteroid.loadFromFile("Sprites/Enemy/asteroidNormal.png");
	asteroid_object.sprite_asteroid.setTexture(asteroid);
	asteroid_object.sprite_asteroid.setScale(.2, .2);
}

void Asteroid::draw_asteroid(RenderWindow& map, Asteroid& asteroid_object)
{
	asteroid_object.Asteroid_animation();
	map.draw(asteroid_object.sprite_asteroid);
}

void Asteroid::asteroid_setPosition(Asteroid& asteroid_object, float x_POS, float y_POS)
{
	asteroid_object.sprite_asteroid.setPosition(x_POS, y_POS);
	asteroid_object.sprite_asteroid.setRotation(-45);
}
