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

void Wave::movementFirstWave(Chicken chicken[5][8])
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{

			float current_x = chicken[i][j].sprite_chicken.getPosition().x;
			float current_y = chicken[i][j].sprite_chicken.getPosition().y;
			if (!left_or_right_movement)
			{
				if (current_x >= 1700) 
				{
					current_x -= 3;
					left_or_right_movement = !left_or_right_movement;
				}
				else
					current_x += 3;
			}
			else
			{
				if (current_x <= 20) 
				{
					current_x += 3;
					left_or_right_movement = !left_or_right_movement;
				}
				else
					current_x -= 3;
			}
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 8; j++)
					chicken[i][j].Animation();
			chicken[i][j].sprite_chicken.setPosition(current_x, current_y);
			//std::cout << chicken[0][0].sprite_chicken.getPosition().x<<' ';
		}

}


