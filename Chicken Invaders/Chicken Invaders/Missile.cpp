#include "Missile.h"
void Missile::MissileAnimation()
{
	m_frame += m_animSpeed;
	if (m_frame > m_frameCount)
		m_frame = 0;
	m_missileSprite.setTextureRect(sf::IntRect(int(m_frame) * 128, 0, 128, 256));
}

Missile::Missile(int shipCenterPosition_x, int shipCenterPosition_y, const sf::Texture& texture)
{
	m_missileSprite.setTexture(texture);
	m_missileSprite.setScale(0.28, 0.28);
	m_missileSprite.setPosition(shipCenterPosition_x + 34, shipCenterPosition_y - 40);
	m_missilePosition_X = shipCenterPosition_x + 34;
	m_missilePosition_Y = shipCenterPosition_y - 40;
	int centerPosition = 1920 / 2;
	int howMuchIWantToRotate_x = (centerPosition - shipCenterPosition_x - 55) / 20;
	m_missileSprite.rotate(howMuchIWantToRotate_x);

}

void Missile::DrawMissile(sf::RenderWindow& GameWindow)
{
	MissileAnimation();
	GameWindow.draw(m_missileSprite);
}

void Missile::UpdatePosition(int shipCenterPosition_x)
{
	//int rotation = m_missileSprite.getRotation();
	int centerX = 1920 / 2, centerY = (1080 / 2) - 100;
	int velocityX = (centerX - m_missilePosition_X) * 0.02;
	int velocityY = (centerY - m_missilePosition_Y) * 0.02;
	//float ActualPositionX = m_missileSprite.getPosition().x;
	//float ActualPositionY = m_missileSprite.getPosition().y;
	//float MovesLeft = (ActualPositionY-centerY) / 5;
	//float HowIMoveX = (ActualPositionX - centerX) / MovesLeft;
	////m_missileSprite.move(HowIMoveX, -5);
	//if (rotation > 180)
	//{   
	//	m_missileSprite.move(-(rotation/50)-1, -5);
	//}
	//if(rotation==0)
	//{
	//	m_missileSprite.move(0, -5);
	//}
	//if (rotation < 180&&rotation!=0)
	//{
	//	m_missileSprite.move(1+(360 - rotation)/50, -5);
	//}
	if (m_missileSprite.getPosition().y > centerY)
		m_missileSprite.move(velocityX, velocityY);


}

Missile& Missile::operator=(const Missile& other)
{
	m_missileSprite = other.m_missileSprite;
	m_missileSprite.setScale(other.m_missileSprite.getScale());
	m_missileSprite.setPosition(other.m_missileSprite.getPosition());
	m_missileSprite.setRotation(other.m_missileSprite.getRotation());
	m_frame = other.m_frame;
	m_frameCount = other.m_frameCount;
	m_animSpeed = other.m_animSpeed;
	m_foodNeeded = other.m_foodNeeded;
	m_missilePosition_X = other.m_missilePosition_X;
	m_missilePosition_Y = other.m_missilePosition_Y;
	return *this;
}

Missile::Missile(Missile&& other) noexcept
{
	m_missileSprite = other.m_missileSprite;
	m_missileSprite.setScale(other.m_missileSprite.getScale());
	m_missileSprite.setPosition(other.m_missileSprite.getPosition());
	m_missileSprite.setRotation(other.m_missileSprite.getRotation());
	m_frame = other.m_frame;
	m_frameCount = other.m_frameCount;
	m_animSpeed = other.m_animSpeed;
	m_foodNeeded = other.m_foodNeeded;
	m_missilePosition_X = other.m_missilePosition_X;
	m_missilePosition_Y = other.m_missilePosition_Y;

}

bool Missile::ItIsTimeForExplosion()
{
	if (m_missileSprite.getPosition().y > (1080 / 2) - 100)
		return true;
	return false;
}

sf::Vector2f Missile::GetPosition()
{
	return m_missileSprite.getPosition();
}
