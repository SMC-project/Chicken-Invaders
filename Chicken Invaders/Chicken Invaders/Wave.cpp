#include "Wave.h"
//
//void Wave::fisrtWavePosition(Chicken chicken[5][8],const int WINDOW_WIDTH,const int WINDOW_HEIGHT)
//{
//
//	for (int i = 0; i < 5; i++)
//		for (int j = 0; j < 8; j++)
//			chicken[i][j].sprite_chicken.setPosition(140*j + WINDOW_WIDTH/4, 120*i + WINDOW_HEIGHT/9);
//	
//}
//
//void Wave::drawWave(RenderWindow& map,Chicken chicken[5][8])
//{
//	for (int i = 0; i < 5; i++)
//		for (int j = 0; j < 8; j++)
//			map.draw(chicken[i][j].sprite_chicken);
//}
//
//void Wave::setSprite(Texture& enemy,Chicken chicken[5][8])
//{
//	enemy.loadFromFile("Sprites/Enemy/chicken.png");
//	for (int i = 0; i < 5; i++)
//		for (int j = 0; j < 8; j++)
//		{
//			chicken[i][j].sprite_chicken.setTexture(enemy);
//			chicken[i][j].sprite_chicken.setScale(0.3,0.3);
//		}
//}
//
//void Wave::movementFirstWave(Chicken chicken[5][8])
//{
//	for (int i = 0; i < 5; i++)
//		for (int j = 0; j < 8; j++)
//		{
//
//			float current_x = chicken[i][j].sprite_chicken.getPosition().x;
//			float current_y = chicken[i][j].sprite_chicken.getPosition().y;
//			if (!left_or_right_movement)
//			{
//				if (current_x >= 1700) 
//				{
//					current_x -= 5;
//					left_or_right_movement = !left_or_right_movement;
//				}
//				else
//					current_x += 5;
//			}
//			else
//			{
//				if (current_x <= 20) 
//				{
//					current_x += 5;
//					left_or_right_movement = !left_or_right_movement;
//					
//					
//				}
//				else
//					current_x -= 5;
//			}
//			for (int i = 0; i < 5; i++)
//				for (int j = 0; j < 8; j++)
//					chicken[i][j].Animation();
//			chicken[i][j].sprite_chicken.setPosition(current_x, current_y);
//			//std::cout << chicken[0][0].sprite_chicken.getPosition().x<<' ';
//		}
//
//}

Wave::Wave()
{
}

void Wave::firstWave(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	for (int index = 0; index < 40; index++)
	{
		chickens.push_back(std::move(Chicken(sf::Vector2f(140 * index + WINDOW_WIDTH / 4, 120 * index + WINDOW_HEIGHT / 9),
			resurceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}
}

void Wave::setPositionWaveOne(std::vector<Chicken>& chickens, int Window_width, int Window_height)
{
	int firstCoord = 0;
	int secondCoord = 0;
	for (int index=0; index < chickens.size(); index++)
	{
		if (secondCoord == 8)
		{
			firstCoord++;
			secondCoord = 0;
		}
		secondCoord++;
		chickens[index].setPositionChicken(140 * secondCoord + Window_width / 4, 120 * firstCoord + Window_height/9);
	}

}

void Wave::firstWaveMovement(std::vector<Chicken> &chickens, RenderWindow& map)
{
	for (int index = 0; index < chickens.size(); index++)
	{
		if (!m_leftOrRightMovement)
			if (chickens[index].getPosition().x >= 1700)
			{
				m_leftOrRightMovement = !m_leftOrRightMovement;
			}
			else
				chickens[index].moveChicken(5, 0);
		else if (m_leftOrRightMovement)
		{
			if (chickens[index].getPosition().x <= 20)
			{
				m_leftOrRightMovement = !m_leftOrRightMovement;
			}
			else
				chickens[index].moveChicken(-5, 0);
		}
	}
}
