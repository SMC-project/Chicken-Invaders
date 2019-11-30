#pragma once
#include<SFML/Graphics.hpp>
class ScrollBackground
{
private:
	sf::Sprite m_backgroundSprite;
	sf::Sprite m_backgroundSprite1;
	float m_pictureHeigh;
public:
	ScrollBackground(const sf::Texture& texture);
	void drawBackground(sf::RenderWindow& gameWindow);
	void AnimateBackground();
};

