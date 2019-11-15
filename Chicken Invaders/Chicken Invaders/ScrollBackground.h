#pragma once
#include<SFML/Graphics.hpp>
class ScrollBackground
{
private:
	sf::Sprite m_backgroundSprite;
	sf::Sprite m_backgroundSprite1;
	sf::Texture m_backgroundTexture;
	float m_pictureHeigh;
public:
	ScrollBackground(const std::string& sprite_name);
	void drawBackground(sf::RenderWindow& gameWindow);
	void AnimateBackground();
};

