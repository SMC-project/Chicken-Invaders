#include "Bullet.h"
#include<Windows.h>

void Bullet::LevelPower(Level currentLevel)
{
	switch (currentLevel)
	{
	case Level::Level_0:
		std::get<2>(m_bullets[0]) = false;
		std::get<2>(m_bullets[1]) = false;
		std::get<2>(m_bullets[2]) = false;
		std::get<2>(m_bullets[3]) = true;
		std::get<2>(m_bullets[4]) = false;
		std::get<2>(m_bullets[5]) = false;
		std::get<2>(m_bullets[6]) = false;
	case Level::Level_1:
		std::get<2>(m_bullets[0]) = false;
		std::get<2>(m_bullets[1]) = false;
		std::get<2>(m_bullets[2]) = true;
		std::get<2>(m_bullets[3]) = false;
		std::get<2>(m_bullets[4]) = true;
		std::get<2>(m_bullets[5]) = false;
		std::get<2>(m_bullets[6]) = false;
		break;
	case Level::Level_2:
		std::get<2>(m_bullets[0]) = false;
		std::get<2>(m_bullets[1]) = false;
		std::get<2>(m_bullets[2]) = true;
		std::get<2>(m_bullets[3]) = true;
		std::get<2>(m_bullets[4]) = true;
		std::get<2>(m_bullets[5]) = false;
		std::get<2>(m_bullets[6]) = false;
		break;
	case Level::Level_3:
		std::get<2>(m_bullets[0]) = false;
		std::get<2>(m_bullets[1]) = true;
		std::get<2>(m_bullets[2]) = false;
		std::get<2>(m_bullets[3]) = true;
		std::get<2>(m_bullets[4]) = false;
		std::get<2>(m_bullets[5]) = true;
		std::get<2>(m_bullets[6]) = false;
		break;
	case Level::Level_4:
		std::get<2>(m_bullets[0]) = true;
		std::get<2>(m_bullets[1]) = true;
		std::get<2>(m_bullets[2]) = false;
		std::get<2>(m_bullets[3]) = false;
		std::get<2>(m_bullets[4]) = false;
		std::get<2>(m_bullets[5]) = true;
		std::get<2>(m_bullets[6]) = true;
		break;
	case Level::Level_5:
		std::get<2>(m_bullets[0]) = true;
		std::get<2>(m_bullets[1]) = true;
		std::get<2>(m_bullets[2]) = false;
		std::get<2>(m_bullets[3]) = true;
		std::get<2>(m_bullets[4]) = false;
		std::get<2>(m_bullets[5]) = true;
		std::get<2>(m_bullets[6]) = true;
		break;
	case Level::Level_6:
		std::get<2>(m_bullets[0]) = true;
		std::get<2>(m_bullets[1]) = true;
		std::get<2>(m_bullets[2]) = true;
		std::get<2>(m_bullets[3]) = false;
		std::get<2>(m_bullets[4]) = true;
		std::get<2>(m_bullets[5]) = true;
		std::get<2>(m_bullets[6]) = true;
		break;
	case Level::Level_7:
		std::get<2>(m_bullets[0]) = true;
		std::get<2>(m_bullets[1]) = true;
		std::get<2>(m_bullets[2]) = true;
		std::get<2>(m_bullets[3]) = true;
		std::get<2>(m_bullets[4]) = true;
		std::get<2>(m_bullets[5]) = true;
		std::get<2>(m_bullets[6]) = true;
		break;
	}

}
Bullet::Bullet(int shipCenterPosition_x, int shipCenterPosition_y)
{
	m_bulletTexture.loadFromFile("Sprites/Weapons/bullet.png");
	sf::Sprite auxSprite;
	auxSprite.setTexture(m_bulletTexture);
	auxSprite.setScale(0.12, 0.12);
	std::pair<int, int>bulletposition;
	for (int i = 0; i < 7; i++)
	{
		m_bulletSprites.push_back(auxSprite);
	}
	for (int i = 0; i < 7; i++)
	{
		m_bullets.push_back(std::make_tuple(1000, 1000, false));
	}
	m_bulletLevel = Level::Level_0;
	std::get<2>(m_bullets[4]) = true;
	m_bulletSprites[4].setPosition(shipCenterPosition_x, shipCenterPosition_y - 10);
	//BulletsPosition_Update();
}

void Bullet::Present_Collected()
{
	m_bulletLevel;
	int currentLevel = static_cast<int>(m_bulletLevel);
	if (currentLevel < 6)
	{
		currentLevel++;
		m_bulletLevel = static_cast<Level>(currentLevel);
		LevelPower(m_bulletLevel);
	}

}

void Bullet::BulletsPosition_Update(int& currentX, int& currentY)
{

	for (int i = 0; i < m_bullets.size(); i++)
	{
		currentY -= 2;
		if (std::get<2>(m_bullets[i]) == true)
		{
			m_bulletSprites[i].setPosition(currentX, currentY);
		}
	}

}

void Bullet::ResetBulletLevel()
{
	m_bulletLevel = Level::Level_0;
	LevelPower(m_bulletLevel);
}

void Bullet::DrawBullet(sf::RenderWindow& gameWindow)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (std::get<2>(m_bullets[i]) == true)
		{
			gameWindow.draw(m_bulletSprites[i]);
		}
	}
}
