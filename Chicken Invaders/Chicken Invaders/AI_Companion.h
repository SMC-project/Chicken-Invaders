#pragma once
#include"SFML/Graphics.hpp"
#include "Chicken.h"
#include"Boss.h"
#include"Asteroid.h"
class AI_Companion
{
private:
	sf::Vector2f m_initialPos;
	sf::Vector2f m_size;		
	sf::Sprite m_sprite;			
	float m_speed = 20;					
	float m_boundryOffset = -40;			
	sf::Vector2f m_movement;

	//The line and column indexes of the sprite to render, the animation has 4 rows of 10 sprites each
	int m_animColFrame = 0;
	int m_animRowFrame = 0;
	//Is active in game
	bool m_active = true;

	//Special Rotation
	bool m_startRotation=false;
	bool m_rotateRight = false;
	int  m_direction = -1;
	const float pi = 3.14159265359;
	float m_angle = 185;
	float m_radius = 100;
	int xPos, yPos;

public:

	void Init(sf::Vector2f initialPos, const sf::Texture& texture);

	void DrawShip(sf::RenderWindow& gameWindow);

	void MoveShip(int WINDOW_WIDTH, sf::Vector2f shipPosition, sf::Vector2f shipSize);
	//Move right is used to know which value to set in the movement vector and the factor for how much to move (max value of 1)
	//For a more detalied explanation check 'm_movement' description
	void SetMovement(bool moveRight, float factor);

	void Animate();

	const sf::Vector2f &GetPosition();

	bool Shoot(std::vector<Chicken> &chickens, std::vector<Asteroid> &asteroids, std::vector<Boss> &boss);

	void ChangeActiveValue();

	void SetActive();
	
	void SetInactive();

	void ChangeCurrentPosition();




};

