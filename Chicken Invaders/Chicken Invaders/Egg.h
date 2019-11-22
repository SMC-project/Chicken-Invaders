#pragma once
#include<SFML/Graphics.hpp>

class Egg
{
public:
	Egg(const std::string& path, sf::Vector2<int> initialPos);
	void FallDown();
	void DrawEgg(sf::RenderWindow& window);

private:
	void CheckBounds(const sf::RenderWindow& window);

private:
	sf::Texture m_textureEgg;
	sf::Sprite m_spriteEgg;

	sf::Vector2<int> m_eggSize;
	float m_speed = 10;
};
