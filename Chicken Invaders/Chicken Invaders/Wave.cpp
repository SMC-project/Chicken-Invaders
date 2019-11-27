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
	enemy.loadFromFile("Sprites/Enemy/chicken.png");
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{
			chicken[i][j].sprite_chicken.setTexture(enemy);
			chicken[i][j].sprite_chicken.setScale(0.3,0.3);
		}
}

void Wave::movementFirstWave(Chicken chicken[5][8],Wave& wave3)
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
					current_x -= 5;
					left_or_right_movement = !left_or_right_movement;
				}
				else
					current_x += 5;
			}
			else
			{
				if (current_x <= 20) 
				{
					current_x += 5;
					left_or_right_movement = !left_or_right_movement;
					wave3.wave_number = 3;
					
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

void Wave::drawWave_asteroid(RenderWindow& map, Asteroid asteroidVect[5][5])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			map.draw(asteroidVect[i][j].sprite_asteroid);
}

void Wave::setSprite_asteroid1(Texture& asteroid, Asteroid asteroidVect[5][5])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
		{
			asteroidVect[i][j].setSprite_asteroid(asteroid, asteroidVect[i][j]);
		}
}

void Wave::thirdWave_Position(Asteroid asteroidVect[5][5])
{
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
		{
			
			random_number = rand() % 900;
			random_number = -random_number;
			int current_x = random_number;

			random_number = rand() % 900;
			random_number = -random_number;
			int current_y = random_number;

			asteroidVect[i][j].asteroid_setPosition(asteroidVect[i][j], current_x, current_y);
		}
}

void Wave::thirdWave_Movement(Asteroid asteroidVect[5][5])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
		{
			float current_x = asteroidVect[i][j].sprite_asteroid.getPosition().x;
			float current_y = asteroidVect[i][j].sprite_asteroid.getPosition().y;
			current_x += 10;
			current_y += 10;

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 5; j++)
					asteroidVect[i][j].Asteroid_animation();

			asteroidVect[i][j].sprite_asteroid.setPosition(current_x, current_y);
		}

}



