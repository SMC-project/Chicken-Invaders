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
	//Valorile sunt irelevante. Este nevoie de initializare
	for (int i = 0; i < 7; i++)
	{
		m_bullets.push_back(std::make_tuple(0, 0, false));
	}
	m_bulletLevel = Level::Level_0;

	std::get<2>(m_bullets[3]) = true;
	for (int i = 0; i < 7; i++)
	{
		//std::get<2>(m_bullets[i]) = true;
		m_bulletSprites[i].setPosition(shipCenterPosition_x - 1 + i * 15, shipCenterPosition_y - 30);
	}
}

Bullet::Bullet(Bullet&& other) noexcept
{
	m_bulletTexture.swap(other.m_bulletTexture);
	sf::Sprite auxSprite;
	for (int i = 0; i < 7; i++)
	{
		m_bulletSprites.push_back(auxSprite);
	}
	for (int i = 0; i < m_bulletSprites.size(); i++)
	{
		m_bulletSprites[i].setTexture(m_bulletTexture);
		m_bulletSprites[i].setScale(other.m_bulletSprites[i].getScale());
		m_bulletSprites[i].setPosition(other.m_bulletSprites[i].getPosition());
		m_bulletSprites[i].setRotation(other.m_bulletSprites[i].getRotation());

	}
	m_bullets = other.m_bullets;
	m_bulletLevel = other.m_bulletLevel;

}

void Bullet::Present_Collected()
{
	m_bulletLevel;
	int currentLevel = static_cast<int>(m_bulletLevel);
	if (currentLevel < 7)
	{
		currentLevel++;
		m_bulletLevel = static_cast<Level>(currentLevel);
		LevelPower(m_bulletLevel);
	}

}

void Bullet::BulletsPosition_Update(const int speed)
{
	for (int i = 0; i < m_bullets.size(); i++)	
		if (std::get<2>(m_bullets[i]) == true)
					m_bulletSprites[i].move(0, speed);

}

bool Bullet::CheckIfBulletIsOnTheScreen(const int screenHeight)
{
	for (int i = 0; i < m_bullets.size(); i++)
		if (std::get<2>(m_bullets[i]) == true && m_bulletSprites[i].getPosition().y > screenHeight)
			return true;
	return false;
}

void Bullet::ResetBulletLevel()
{
	m_bulletLevel = Level::Level_0;
	LevelPower(m_bulletLevel);
}

void Bullet::Shot(sf::RenderWindow& gameWindow)
{
	DrawBullet(gameWindow);
	BulletsPosition_Update(m_bulletSpeed);
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



Bullet& Bullet::operator=(const Bullet& other)
{
	sf::Texture aux = other.m_bulletTexture;
	m_bulletTexture.swap(aux);
	
	for (int i = 0; i < m_bulletSprites.size(); i++)
	{
		m_bulletSprites[i].setTexture(m_bulletTexture);
		m_bulletSprites[i].setScale(other.m_bulletSprites[i].getScale());
		m_bulletSprites[i].setPosition(other.m_bulletSprites[i].getPosition());
		m_bulletSprites[i].setRotation(other.m_bulletSprites[i].getRotation());	
	}
	m_bullets = other.m_bullets;
	m_bulletLevel = other.m_bulletLevel;
	return *this;
}
