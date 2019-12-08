#include "Chicken.h"



Chicken::Chicken(Vector2f initialPos, const Texture& texture)
{
	m_chickenSprite.setTexture(texture);
	m_chickenSprite.setScale(.3, .3);
	m_chickenSize= Vector2f(256 * m_chickenSprite.getScale().x, 256 * m_chickenSprite.getScale().y);
	initialPos.x -= m_chickenSize.x / 3;
	initialPos.y -= m_chickenSize.y / 3;
	m_chickenSprite.setPosition(initialPos.x, initialPos.y);
}
Chicken::Chicken(Chicken&& other) noexcept
{
	m_chickenSprite.setTexture(*other.m_chickenSprite.getTexture());

	m_chickenSprite.setScale(other.m_chickenSprite.getScale());
	m_chickenSize = other.m_chickenSize;
	m_chickenSprite.setPosition(other.m_chickenSprite.getPosition());

	m_chickenIndex = other.m_chickenIndex;
}

Chicken& Chicken::operator=(const Chicken& other)
{
	m_chickenSprite.setTexture(*other.m_chickenSprite.getTexture());

	m_chickenSprite.setScale(other.m_chickenSprite.getScale());
	m_chickenSize = other.m_chickenSize;
	m_chickenSprite.setPosition(other.m_chickenSprite.getPosition());

	m_chickenIndex = other.m_chickenIndex;

	return *this;
}

void Chicken::chickenAnimation()
{
	frameChicken += animeSpeedChicken;
	if (frameChicken > frameCountchicken)
		frameChicken = 0;
	m_chickenSprite.setTextureRect(IntRect(int(frameChicken) * 256, 0, 256, 256));
}

void Chicken::drawChicken(RenderWindow& map)
{
	chickenAnimation();
	map.draw(m_chickenSprite);
}

void Chicken::setPositionChicken(float posX, float posY)
{
	m_chickenSprite.setPosition(posX, posY);
}

void Chicken::moveChicken(float posX, float posY)
{
	m_chickenSprite.move(posX, posY);
}



sf::Vector2f Chicken::getPosition()
{
	return m_chickenSprite.getPosition();
}

sf::Vector2f Chicken::getSize()
{
	return m_chickenSize;
}

const sf::Sprite& Chicken::GetSprite() { return m_chickenSprite; }

//Used for wave 4 and 5
void Chicken::SetChickenIndex(int index) { m_chickenIndex = index; }
int Chicken::GetChickenIndex() { return m_chickenIndex; }