#pragma once
#include<SFML/Graphics.hpp>

class Meat
{
public:
	Meat(sf::Vector2f initialPos, const sf::Texture& texture);
	Meat(Meat&& other) noexcept;
	//Operator= needed for move constructor
	Meat& operator=(const Meat& other);

	bool Move();
	void Draw(sf::RenderWindow& gameWindow);

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();

private:
	sf::Sprite m_sprite;

	sf::Vector2f m_size;
	sf::Vector2f m_velocity;	//Retains the direction and the speed for movement
};

