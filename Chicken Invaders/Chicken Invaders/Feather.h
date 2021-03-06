#pragma once
#include"SFML/Graphics.hpp"


class Feather
{
private:
	sf::Sprite m_sprite;

	sf::Vector2f m_size;
	sf::Vector2f m_velocity;	//Retains the direction and the speed for movement
	const float m_accelerationFact = 0.1f;
	float m_rotationSpeed;

	float m_rotationFact = 1;
	float m_destroyTime;

public:
	Feather(sf::Vector2f initialPos, const sf::Texture& texture);
	Feather(Feather&& other) noexcept;
	//Operator= needed for move constructor
	Feather& operator=(const Feather&& other) noexcept;
	bool Move(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT, float deltaTimeSeconds);
	void Draw(sf::RenderWindow& gameWindow);
};

