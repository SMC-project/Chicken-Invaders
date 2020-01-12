#pragma once
#include"SFML/Graphics.hpp"
class AI_Companion
{
private:
	sf::Vector2f m_initialPos;
	sf::Vector2f m_Size;		
	sf::Sprite m_sprite;			
	float m_speed = 20;					
	float m_boundryOffset = 50;			
	sf::Vector2f m_movement;

	//The line and column indexes of the sprite to render, the animation has 4 rows of 10 sprites each
	int m_animColFrame = 0;
	int m_animRowFrame = 0;
	//Is active in game
	bool m_active = false;

public:

	void Init(sf::Vector2f initialPos, const sf::Texture& texture);

	void DrawShip(sf::RenderWindow& gameWindow);

	void MoveShip(int WINDOW_WIDTH);
	//Move right is used to know which value to set in the movement vector and the factor for how much to move (max value of 1)
	//For a more detalied explanation check 'm_movement' description
	void SetMovement(bool moveRight, float factor);
	void Animate();
	sf::Vector2f GetPosition();

	bool Shoot();



};

