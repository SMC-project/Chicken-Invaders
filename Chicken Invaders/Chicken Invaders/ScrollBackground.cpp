#include "ScrollBackground.h"
ScrollBackground::ScrollBackground(const std::string& spriteName)

{
	m_backgroundTexture.loadFromFile(spriteName);
	m_backgroundSprite.setTexture(m_backgroundTexture);	
	m_backgroundSprite.setScale(2, 2);
	m_backgroundSprite1.setTexture(m_backgroundTexture);
	m_backgroundSprite1.setScale(2, 2);
	m_pictureHeigh = m_backgroundTexture.getSize().y * m_backgroundSprite.getScale().y;
	m_backgroundSprite1.setPosition(0, -m_pictureHeigh);
	m_backgroundSprite.setPosition(0, -(m_pictureHeigh - 1080));

}

void ScrollBackground::drawBackground(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_backgroundSprite1);
	gameWindow.draw(m_backgroundSprite);
}

void ScrollBackground::AnimateBackground()
{   
	float current_x = m_backgroundSprite.getPosition().x;
	float current_y = m_backgroundSprite.getPosition().y;
	float secondspriteY =m_backgroundSprite.getPosition().y-(m_pictureHeigh);
	current_y += 8;
	secondspriteY += 8;
	if (current_y >= 1080)
	{
		current_y = -(m_pictureHeigh - 1080);
		secondspriteY = -m_pictureHeigh;
	}
	m_backgroundSprite1.setPosition(current_x, secondspriteY);
	m_backgroundSprite.setPosition(current_x, current_y);
	
}
