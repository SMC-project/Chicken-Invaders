#include "ScrollBackground.h"
ScrollBackground::ScrollBackground(const std::string& spriteName)

{
	m_backgroundTexture.loadFromFile(spriteName);
	m_backgroundSprite.setTexture(m_backgroundTexture);	
	m_backgroundSprite.setScale(2, 2);
	m_pictureHeigh = m_backgroundTexture.getSize().y * m_backgroundSprite.getScale().y;
	m_backgroundSprite.setPosition(0, -(m_pictureHeigh - 1080));
}

void ScrollBackground::drawBackground(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_backgroundSprite);
}

void ScrollBackground::AnimateBackground()
{   
	float current_x = m_backgroundSprite.getPosition().x;
	float current_y = m_backgroundSprite.getPosition().y;
	current_y += 8;
	if (current_y >= 0)
		current_y = -(m_pictureHeigh-1080);
	
	m_backgroundSprite.setPosition(current_x, current_y);

}
