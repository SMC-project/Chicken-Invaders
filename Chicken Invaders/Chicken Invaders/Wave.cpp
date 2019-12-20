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
	float randScale;
	float random_number;
	float randSpeed;
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
		randScale = rand() % 4 + 2;
		randScale = randScale / 10.0f;
		randSpeed = rand() % 30 + 10;
		asteroids[index].setAsteroidsSpeed(randSpeed);
		asteroids[index].serScale(randScale);
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
	float randScale;
	float randSpeed;
	srand(time(NULL));
	for (int index = 0; index < 40; index++)
	{
		randomNumber = rand() % 1920 + rand() % 1000;
		float currentX = randomNumber;

		randomNumber = rand() % 1920 + rand() % 200;
		randomNumber = -randomNumber;
		float currentY = randomNumber;
		asteroids.push_back(std::move(Asteroid(Vector2f(currentX, currentY), texture)));
	}
	for (int index = 0; index < asteroids.size(); index++)
	{
		randScale = rand() % 4 + 2;
		randScale = randScale / 10.0f;
		
		
		randSpeed = rand() % 20 + 10;
		std::cout << randSpeed << " ";
		asteroids[index].serScale(randScale);
		asteroids[index].setRotation(0);
		asteroids[index].setAsteroidsSpeed(randSpeed);
	}
}

void Wave::wave6Movement(std::vector<Asteroid>& asteroids, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int index = 0; index < asteroids.size(); index++)
	{
		
		asteroids[index].Falldown(SCREEN_HEIGHT, 0, asteroids[index].getasteroidsSpeed());
	}
}

void Wave::Wave8Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int i = 0; i < 16; i++)
	{
		chickens.push_back(std::move(Chicken(Vector2f(SCREEN_WIDTH - i * 100 - 10, 200), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}
	for (int i = 0; i < 16; i++)
	{
		chickens.push_back(std::move(Chicken(Vector2f(i * 100 + 10, 100), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}

}

void Wave::Wave8Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int index = 0; index < chickens.size()/2; index++)
	{	
		chickens[index].moveChicken(-7, 7);
	}

	for (int index = chickens.size()/2; index < chickens.size(); index++)
	{
		chickens[index].moveChicken(7, 7);
	}
}



void Wave::Wave7Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int i = 0; i < 8; i++)
	{
		chickens.push_back(std::move(Chicken(Vector2f(i * 140 + 100, 250), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}
	for (int i = 0; i < 8; i++)
	{
		chickens.push_back(std::move(Chicken(Vector2f(SCREEN_WIDTH-i * 140 - 100, 100), resourceLoader.GetTexture(ResourceLoader::TextureType::Chicken))));
	}
}

void Wave::Wave7Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int i = 0; i < chickens.size()/2; i++)
	{
		if (m_wave7_left_right[i] == 0)
			if (chickens[i].getPosition().x >= 1700)
			{
				m_wave7_left_right[i] = 1;
			}
			else
				chickens[i].moveChicken(6, 1);
		else if(m_wave7_left_right[i] == 1)
			if (chickens[i].getPosition().x <= 20)
			{
				m_wave7_left_right[i] = 0;
			}
			else
				chickens[i].moveChicken(-6, 1 );
	}

	for (int i = chickens.size() / 2; i < chickens.size(); i++)
	{
		if (m_wave7_left_right2[i] == 0)
			if (chickens[i].getPosition().x >= 1700)
			{
				m_wave7_left_right2[i] = 1;
			}
			else
				chickens[i].moveChicken(6, 1);
		else if (m_wave7_left_right2[i] == 1)
			if (chickens[i].getPosition().x <= 20)
			{
				m_wave7_left_right2[i] = 0;
			}
			else
				chickens[i].moveChicken(-6, 1);
	}
}
void Wave::Wave9Init(std::vector<Asteroid>& asteroids, const Texture& texture, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	float randScale;
	float randomNumber;
	float direction;
	float randSpeed;
	srand(time(NULL));
	for (int index = 0; index < 40; index++)
	{
		direction = rand() % 3 + 1;
		if (direction == 1)
		{
			randomNumber = rand() % 900 + rand() % 100;
			randomNumber = -randomNumber;
			float currentX = randomNumber;

			randomNumber = rand() % 900 + rand() % 100;
			randomNumber = -randomNumber;
			float currentY = randomNumber;
			asteroids.push_back(std::move(Asteroid(sf::Vector2f(currentX, currentY), texture)));
			asteroids[asteroids.size() - 1].setVelocity(direction);
		}
		if (direction == 2)
		{
			randomNumber = rand() % 1920 + rand() % 1000;
			float currentX = randomNumber;

			randomNumber = rand() % 1080 + rand() % 200;
			randomNumber = -randomNumber;
			float currentY = randomNumber;
			asteroids.push_back(std::move(Asteroid(sf::Vector2f(currentX, currentY), texture)));
			asteroids[asteroids.size() - 1].setVelocity(direction);
		}
		if (direction == 3)
		{
	
			randomNumber = rand() % 1920 + 1800 + rand() % 100;
		
			float currentX = randomNumber;

			randomNumber = rand() % 900 + 400 + rand() % 100;
			randomNumber = -randomNumber;
			float currentY = randomNumber;
			asteroids.push_back(std::move(Asteroid(sf::Vector2f(currentX, currentY), texture)));
			asteroids[asteroids.size() - 1].setVelocity(direction);
		}
	}
	for (int index = 0; index < asteroids.size(); index++)
	{
		if (asteroids[index].getVelocity() == 1)
			asteroids[index].setRotation(-45);
		else if (asteroids[index].getVelocity() == 2)
			asteroids[index].setRotation(0);
		else if (asteroids[index].getVelocity() == 3)
			asteroids[index].setRotation(45);
		randScale = rand() % 4 + 2;
		randScale = randScale / 10.0f;
		randSpeed = rand() % 20 + 10;
		
		asteroids[index].setAsteroidsSpeed(randSpeed);
		asteroids[index].serScale(randScale);
	}
}

void Wave::Wave9Movement(std::vector<Asteroid>& asteroids, int SCRENN_WIDTH, int SCREEN_HEIGHT)
{
	for (int index = 0; index < asteroids.size(); index++) {
		if (asteroids[index].getVelocity() == 1)
			asteroids[index].Falldown(SCREEN_HEIGHT, asteroids[index].getasteroidsSpeed()-10, asteroids[index].getasteroidsSpeed()-10);
		else if (asteroids[index].getVelocity() == 2)
			asteroids[index].Falldown(SCREEN_HEIGHT, 0, asteroids[index].getasteroidsSpeed());
		else if (asteroids[index].getVelocity() == 3)
			asteroids[index].Falldown(SCREEN_HEIGHT, -asteroids[index].getasteroidsSpeed()+10, asteroids[index].getasteroidsSpeed()-10);
	
	}
}

void Wave::Wave10Init(std::vector<Boss> &bosses, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	bosses.emplace_back(std::move(Boss(resourceLoader.GetTexture(ResourceLoader::TextureType::Boss),1,700,50)));
}

void Wave::Wave10Movement(std::vector<Boss> &bosses, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	for (int index = 0; index < bosses.size(); index++)
	{
		if (!m_leftOrRightMovement)
			if (bosses[index].GetPosition().x >= 1400)
			{
				m_leftOrRightMovement = !m_leftOrRightMovement;
			}
			else
				bosses[index].UpdatePosition(8, 0);
		else if (m_leftOrRightMovement)
		{
			if (bosses[index].GetPosition().x <= 20)
			{
				m_leftOrRightMovement = !m_leftOrRightMovement;
			}
			else
				bosses[index].UpdatePosition(-8, 0);
		}
	}
}
