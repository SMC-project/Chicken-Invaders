#include "Chicken.h"



Chicken::Chicken(Vector2f initialPos, const Texture& texture)
{
	m_chickenSprite.setTexture(texture);
	m_chickenSprite.setScale(.3, .3);
	m_chickenSize= Vector2f(256 * m_chickenSprite.getScale().x, 256 * m_chickenSprite.getScale().y);
	initialPos.x -= m_chickenSize.x / 3;
	initialPos.y -= m_chickenSize.y / 3;
	m_chickenSprite.setPosition(initialPos.x, initialPos.y);

	//Used for the default animation (first row in sprite sheet)
	m_startFrameLine = 0;
	m_endFrameLine = 0;
	m_frameLine = m_startFrameLine;
}
Chicken::Chicken(Chicken&& other) noexcept
{
	m_chickenSprite.setTexture(*other.m_chickenSprite.getTexture());

	m_chickenSprite.setScale(other.m_chickenSprite.getScale());
	m_chickenSize = other.m_chickenSize;
	m_chickenSprite.setPosition(other.m_chickenSprite.getPosition());

	m_chickenIndex = other.m_chickenIndex;

	//Used for the default animation (first row in sprite sheet)
	m_startFrameLine = other.m_startFrameLine;
	m_endFrameLine = other.m_endFrameLine;
	m_frameLine = m_startFrameLine;
	m_frameCol = other.m_frameCol;
	m_moveDirectionFact = other.m_moveDirectionFact;
	m_xOffsetFact = other.m_xOffsetFact;
	m_yOffsetFact = other.m_yOffsetFact;
}

Chicken& Chicken::operator=(const Chicken& other)
{
	m_chickenSprite.setTexture(*other.m_chickenSprite.getTexture());

	m_chickenSprite.setScale(other.m_chickenSprite.getScale());
	m_chickenSize = other.m_chickenSize;
	m_chickenSprite.setPosition(other.m_chickenSprite.getPosition());

	m_chickenIndex = other.m_chickenIndex;

	//Used for the default animation (first row in sprite sheet)
	m_startFrameLine = other.m_startFrameLine;
	m_endFrameLine = other.m_endFrameLine;
	m_frameLine = m_startFrameLine;
	m_frameCol = other.m_frameCol;
	m_moveDirectionFact = other.m_moveDirectionFact;
	m_xOffsetFact = other.m_xOffsetFact;
	m_yOffsetFact = other.m_yOffsetFact;

	return *this;
}

void Chicken::chickenAnimation()
{
	m_frameCol += m_animSpeed;
	if (m_frameCol >= m_frameCount)
	{
		m_frameCol = 0;
		if (m_startFrameLine != m_endFrameLine)
		{
			if (m_frameLine < m_endFrameLine)
				m_frameLine++;
			else
				m_frameLine = m_startFrameLine;
		}
	}
	m_chickenSprite.setTextureRect(IntRect(int(m_frameCol) * 256, m_frameLine * 256, 256, 256));
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

float Chicken::getChickenScore()
{
	return m_scoreChicken;
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
void Chicken::SetAnimationFrames(int startLine, int endLine)
{
	m_startFrameLine = startLine;
	m_endFrameLine = endLine;

	m_frameLine = m_startFrameLine;
}
