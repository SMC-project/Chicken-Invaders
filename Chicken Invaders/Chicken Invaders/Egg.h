#pragma once
#include<SFML/Graphics.hpp>

class Egg
{
public:
	//Default constructor of the egg, it load a testure, sets the sprite's texture, scale, position and calculates the size
	Egg(sf::Vector2f initialPos, const sf::Texture& texture);
	//Move constructor; needed for inserting (temporary) eggs into the eggs vector
	Egg(Egg&& other) noexcept;
	bool FallDown(int screenHeight);	//Move the egg downwards and return true if it exits the screen
	void DrawEgg(sf::RenderWindow& window);	//Draw the egg on the screen

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();

	//Operator= needed for move constructor
	Egg& operator=(const Egg& other);

private:
	sf::Sprite m_spriteEgg;

	sf::Vector2f m_eggSize;
	float m_speed = 10;	//The speed with which it falls
};
