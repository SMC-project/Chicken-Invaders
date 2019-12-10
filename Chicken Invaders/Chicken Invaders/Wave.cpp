#include "Wave.h"
#include <iomanip>
#include <iostream>
void Wave::Wave1Init(std::vector<Chicken>& chickens, const Texture& texture, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	for (int index = 0; index < 40; index++)
	{
		chickens.push_back(std::move(Chicken(sf::Vector2f(140 * index + WINDOW_WIDTH / 4, 120 * index + WINDOW_HEIGHT / 9), texture)));
	}
}

void Wave::Wave1SetPosition(std::vector<Chicken>& chickens, int Window_width, int Window_height)
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

void Wave::Wave1Movement(std::vector<Chicken> &chickens)
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

void Wave::Wave3Init(const Texture& texture, std::vector<Asteroid>& asteroids)
{
	float random_number;
	for (int index = 0; index < 15; index++)
	{
		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_x = random_number;

		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_y = random_number;

		asteroids.push_back(std::move(Asteroid(sf::Vector2f(current_x, current_y), texture)));
	}
	for (int index = 0; index < asteroids.size(); index++)
	{
		asteroids[index].setRotation(-45);
	}
}

void Wave::Wave4And5Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	float fact = 360.0f / wave4and5NrChickens;
	float xPos, yPos;
	int direction;
	int offsetFact1, offsetFact2;
	for (int index = 0; index <= wave4and5NrChickens; index++)
	{
		direction = rand() % 2 == 1 ? 1 : -1;
		offsetFact1 = rand() % 100;
		offsetFact2 = rand() % 100;

		xPos = direction * sin(index * fact * pi / 180) * (radius1 + offsetFact1) + (SCREEN_WIDTH) / 2;
		yPos = cos(index * fact * pi / 180) * (radius2 + offsetFact2) + (SCREEN_HEIGHT) / 3;
		chickens.push_back(std::move(Chicken(Vector2f(xPos, yPos), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
		chickens[chickens.size() - 1].m_chickenIndex = index;
		chickens[chickens.size() - 1].SetAnimationFrames(0, 0);
		chickens[chickens.size() - 1].m_moveDirectionFact = direction;
		chickens[chickens.size() - 1].m_xOffsetFact = offsetFact1;
		chickens[chickens.size() - 1].m_yOffsetFact = offsetFact2;
	}
}

void Wave::Wave4And5Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	degrees += 1;
	if (degrees == 360)
		degrees = 0;
	float fact = 360.0f / wave4and5NrChickens;
	float xPos, yPos;
	for (int index = 0; index < chickens.size(); index++)
	{
		xPos = chickens[index].m_moveDirectionFact * sin((degrees + chickens[index].m_chickenIndex * fact) * pi / 180) * (radius1 + chickens[index].m_xOffsetFact) + (SCREEN_WIDTH - 128) / 2;
		yPos = cos((degrees + chickens[index].m_chickenIndex * fact) * pi / 180) * (radius2 + chickens[index].m_yOffsetFact) + (SCREEN_HEIGHT - 128) / 3;
		chickens[index].setPositionChicken(xPos, yPos);
	}
}

void Wave::wave6Init(std::vector<Asteroid>& asteroids, const Texture& texture, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	float randomNumber;
	srand(time(NULL));
	for (int index = 0; index < 40; index++)
	{
		randomNumber = rand() % 1920 + rand() % 1000;
		float currentX = randomNumber;

		randomNumber = rand() % 1080 + rand() % 200;
		randomNumber = -randomNumber;
		float currentY = randomNumber;
		asteroids.push_back(std::move(Asteroid(Vector2f(currentX, currentY), texture)));
	}
	for (int index = 0; index < asteroids.size(); index++)
	{
		asteroids[index].setRotation(0);
	}
}

void Wave::wave6Movement(std::vector<Asteroid>& asteroids, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int index = 0; index < asteroids.size(); index++)
	{
		asteroids[index].Falldown(SCREEN_HEIGHT, 0, 20);
	}
}

void Wave::Wave7Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int i = 0; i < 4; i++)
	{
		chickens.push_back(std::move(Chicken(Vector2f(SCREEN_WIDTH - i * 180 - 10, 200), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}
	for (int i = 0; i < 4; i++)
	{
		chickens.push_back(std::move(Chicken(Vector2f(i * 180 + 10, 300), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}

}

void Wave::Wave7Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int index = 0; index < chickens.size()-4; index++)
	{
		if (!m_wave7_left_right)
			if (chickens[index].getPosition().x >= 1700)
			{
				m_wave7_left_right = !m_wave7_left_right;
			}
			else
				chickens[index].moveChicken(5, .2);
		else if (m_wave7_left_right)
		{
			if (chickens[index].getPosition().x <= 20)
			{
				m_wave7_left_right = !m_wave7_left_right;
			}
			else
				chickens[index].moveChicken(-5, .2);
		}
	}

	for (int index = chickens.size() - 4; index < chickens.size(); index++)
	{
		if (!m_wave7_left_right2)
			if (chickens[index].getPosition().x >= 1700)
			{
				m_wave7_left_right2 = !m_wave7_left_right2;
			}
			else
				chickens[index].moveChicken(5, .2);
		else if (m_wave7_left_right2)
		{
			if (chickens[index].getPosition().x <= 20)
			{
				m_wave7_left_right2 = !m_wave7_left_right2;
			}
			else
				chickens[index].moveChicken(-5, .2);
		}
	}
}
