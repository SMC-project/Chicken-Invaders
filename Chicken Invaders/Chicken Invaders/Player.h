#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>

class Player
{
public:
	Player(const std::string& spritePath, std::pair<int, int> initialPos);

	void DrawShip(sf::RenderWindow& gameWindow);
	void MoveShip(int WINDOW_WIDTH);
	void SetMoveDirection(int direction);

private:
	std::pair<int, int> m_shipPosition;
	std::pair<int, int> m_shipSize;
	sf::Sprite m_sprite_ship;
	sf::Texture m_texture_ship;

	float m_speed = 20;
	float m_boundryOffset = 50;
	float m_moveDirection = 0;
};

