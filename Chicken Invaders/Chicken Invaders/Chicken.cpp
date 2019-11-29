#include "Chicken.h"



Chicken::Chicken(sf::Vector2f initialPos)
{
	m_chickenTextrue.loadFromFile("Sprites/Enemy/chicken.png");
	m_chickenSprite.setTexture(m_chickenTextrue);
	m_chickenSprite.setScale(.3, .3);
	m_chickenSize= Vector2f(m_chickenTextrue.getSize().x * m_chickenSprite.getScale().x, m_chickenTextrue.getSize().y* m_chickenSprite.getScale().y);
	
	initialPos.x -= m_chickenSize.x / 3;
	initialPos.y -= m_chickenSize.y / 3;
	m_chickenSprite.setPosition(initialPos.x, initialPos.y);
}
Chicken::Chicken(Chicken&& other) noexcept
{
	m_chickenTextrue.swap(other.m_chickenTextrue);
	m_chickenSprite.setTexture(other.m_chickenTextrue);

	m_chickenSprite.setScale(other.m_chickenSprite.getScale());
	m_chickenSize = other.m_chickenSize;
	m_chickenSprite.setPosition(other.m_chickenSprite.getPosition());

}

void Chicken::chickenAnimation()
{
	frameChicken += animeSpeedChicken;
	if (frameChicken > frameCountchicken)frameChicken = 0;
	m_chickenSprite.setTextureRect(IntRect(int(frameChicken) * 256, 0, 256, 11520));
}

Chicken& Chicken::operator=(const Chicken& other)
{
	Texture temp = other.m_chickenTextrue;
	m_chickenTextrue.swap(temp);
	m_chickenSprite.setTexture(m_chickenTextrue);

	m_chickenSprite.setScale(other.m_chickenSprite.getScale());
	m_chickenSize = other.m_chickenSize;
	m_chickenSprite.setPosition(other.m_chickenSprite.getPosition());

	return *this ;
}

void Chicken::drawChicken(RenderWindow& map)
{
	chickenAnimation();
	map.draw(m_chickenSprite);
}

void Chicken::setPositionChicken(Chicken& chicken, float posX, float posY)
{
	chicken.m_chickenSprite.setPosition(posX, posY);
}

bool Chicken::chickenMovement(int screenWidth)
{
	
	if (m_chickenSprite.getPosition().x >= 1700)
	{
		m_chickenSprite.move(-10, 0);
		return true;
	}
	else if (m_chickenSprite.getPosition().x <= 20)
	{
		m_chickenSprite.move(10, 0);
		return false;
	}
}

sf::Vector2f Chicken::getPosition()
{
	return m_chickenSprite.getPosition();
}

sf::Vector2f Chicken::getSize()
{
	return m_chickenSize;
}