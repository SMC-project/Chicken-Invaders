#include "Bullet.h"
#include<Windows.h>
void Bullet::LevelPower(Level currentLevel)
{
	switch (currentLevel)
	{
	case Level::Level_0:
		m_bullets[0].second = false;
		m_bullets[1].second = false;
		m_bullets[2].second = false;
		m_bullets[3].second = true;
		m_bullets[4].second = false;
		m_bullets[5].second = false;
		m_bullets[6].second = false;
	case Level::Level_1:
		m_bullets[0].second = false;
		m_bullets[1].second = false;
		m_bullets[2].second = true;
		m_bullets[3].second = false;
		m_bullets[4].second = true;
		m_bullets[5].second = false;
		m_bullets[6].second = false;
		break;
	case Level::Level_2:
		m_bullets[0].second = false;
		m_bullets[1].second = false;
		m_bullets[2].second = true;
		m_bullets[3].second = true;
		m_bullets[4].second = true;
		m_bullets[5].second = false;
		m_bullets[6].second = false;
		break;
	case Level::Level_3:
		m_bullets[0].second = false;
		m_bullets[1].second = true;
		m_bullets[2].second = false;
		m_bullets[3].second = true;
		m_bullets[4].second = false;
		m_bullets[5].second = true;
		m_bullets[6].second = false;
		break;
	case Level::Level_4:
		m_bullets[0].second = true;
		m_bullets[1].second = true;
		m_bullets[2].second = false;
		m_bullets[3].second = false;
		m_bullets[4].second = false;
		m_bullets[5].second = true;
		m_bullets[6].second = true;
		break;
	case Level::Level_5:
		m_bullets[0].second = true;
		m_bullets[1].second = true;
		m_bullets[2].second = false;
		m_bullets[3].second = true;
		m_bullets[4].second = false;
		m_bullets[5].second = true;
		m_bullets[6].second = true;
		break;
	case Level::Level_6:
		m_bullets[0].second = true;
		m_bullets[1].second = true;
		m_bullets[2].second = true;
		m_bullets[3].second = false;
		m_bullets[4].second = true;
		m_bullets[5].second = true;
		m_bullets[6].second = true;
		break;
	case Level::Level_7:
		m_bullets[0].second = true;
		m_bullets[1].second = true;
		m_bullets[2].second = true;
		m_bullets[3].second = true;
		m_bullets[4].second = true;
		m_bullets[5].second = true;
		m_bullets[6].second = true;
		break;
	}
	
}
Bullet::Bullet(std::pair<int, int> shipCenterPosition)
{
	m_bulletLevel = Level::Level_0;
	for (int index = 0; index < 7; index++)
	{
		m_bullets[index].first.first = shipCenterPosition.first - 4 + index;
		m_bullets[index].first.second = shipCenterPosition.second - 1;
		m_bullets[index].second = false;
	}
	m_bullets[4].second = true;
	
}

void Bullet::Present_Collected()
{
	m_bulletLevel;
	int currentLevel =(int)m_bulletLevel;
	if (currentLevel < 6)
	{
		currentLevel++;
		m_bulletLevel = (Level)currentLevel;
		LevelPower(m_bulletLevel);
    }

}

void Bullet::BulletsPosition_Update()
{


}

void Bullet::ResetShipLevel()
{
	m_bulletLevel = Level::Level_0;
	LevelPower(m_bulletLevel);
}
