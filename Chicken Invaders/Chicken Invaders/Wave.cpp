#include "Wave.h"

void Wave::fisrtWavePosition(Chicken chicken[5][8],const int WINDOW_WIDTH,const int WINDOW_HEIGHT)
{

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
			chicken[i][j].sprite_chicken.setPosition(140*j + WINDOW_WIDTH/4, 120*i + WINDOW_HEIGHT/9);
	
}

void Wave::drawWave(RenderWindow& map,Chicken chicken[5][8])
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
			map.draw(chicken[i][j].sprite_chicken);
}

void Wave::setSprite(Texture& enemy,Chicken chicken[5][8])
{
	enemy.loadFromFile("Sprites/Enemy/Normal Chicken/Idle/chicken_animation.png");
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{
			chicken[i][j].sprite_chicken.setTexture(enemy);
			chicken[i][j].sprite_chicken.setScale(0.3,0.3);
		}
}

void Wave::movementFirstWave(Chicken chicken[5][8] , Chicken explosion)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{

			float current_x = chicken[i][j].sprite_chicken.getPosition().x;
			float current_y = chicken[i][j].sprite_chicken.getPosition().y;
			if (!left_or_right_movement)
			{

				

				if (current_x >= 1700) {
					current_x -= 5;
					left_or_right_movement = !left_or_right_movement;
				}
				else
					current_x += 5;

			}
			else
			{
				if (current_x <= 20) {
					current_x += 5;
					left_or_right_movement = !left_or_right_movement;
				}
				else
					current_x -= 5;

			}
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 8; j++)
					chicken[i][j].Animation();
			chicken[i][j].sprite_chicken.setPosition(current_x, current_y);
			//std::cout << chicken[0][0].sprite_chicken.getPosition().x<<' ';
		}

}

void Wave::setSprite_explosion(Texture& explosion, Chicken& chicken_explode)
{
	explosion.loadFromFile("Sprites/Enemy/Normal Chicken/Explosion/type_C.png");
	chicken_explode.sprite_explosion.setTexture(explosion);
	chicken_explode.sprite_explosion.setScale(.5, .5);
}

void Wave::draw_explosion(RenderWindow& map, Chicken& explode)
{
	explode.explosion();
	map.draw(explode.sprite_explosion);

}

void Wave::explosion_setPosition(Chicken& object, float x_POS, float y_POS)
{
	object.sprite_explosion.setPosition(x_POS, y_POS);
}

void Wave::setSprite_asteroid(Texture& asteroid, Asteroid& asteroid_object)
{
	asteroid.loadFromFile("Sprites/Enemy/asteroidNormal.png");
	asteroid_object.sprite_asteroid.setTexture(asteroid);
	asteroid_object.sprite_asteroid.setScale(.2, .2);
}

void Wave::draw_asteroid(RenderWindow& map, Asteroid& asteroid_object)
{
	asteroid_object.Asteroid_animation();
	map.draw(asteroid_object.sprite_asteroid);
}

void Wave::asteroid_setPosition(Asteroid& asteroid_object, float x_POS, float y_POS)
{
	asteroid_object.sprite_asteroid.setPosition(x_POS, y_POS);
	asteroid_object.sprite_asteroid.setRotation(-45);
}


