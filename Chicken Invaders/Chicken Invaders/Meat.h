#pragma once
#include<SFML/Graphics.hpp>

class Meat
{
public:
	Meat(sf::Vector2f initialPos, const sf::Texture& texture);
	Meat(Meat&& other) noexcept;
	//Operator= needed for move constructor
	Meat& operator=(const Meat& other);

	bool Move(int SCREEN_WIDTH, int SCREEN_HEIGHT, float deltaTime);
	void Draw(sf::RenderWindow& gameWindow);
	float getMeatScore();

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	const sf::Sprite& GetSprite();

private:
	sf::Sprite m_sprite;

	sf::Vector2f m_size;
	sf::Vector2f m_velocity;	//Retains the direction and the speed for movement
	float m_accelerationFact = 0.1f;
	float m_rotationSpeed;

	float m_rotationFact = 1;
	float m_bounce = 0;
	float m_sideBounce = 0;
	float m_destroyTime;
	float m_meatScore=10;
};

