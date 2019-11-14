#include "Player.h"

Player::Player(const std::string& spritePath, std::pair<int, int> initialPos)
{
	m_shipPosition = initialPos;
	m_texture_ship.loadFromFile(spritePath);
	m_sprite_ship.setTexture(m_texture_ship);

	//Resize the sprite so that it doesn't cover too much space
	m_sprite_ship.setScale(0.15f, 0.15f);
	//Retain how many pixels the ship covers because we will need it later for collision check
	m_shipSize = std::make_pair(m_sprite_ship.getTexture()->getSize().x * m_sprite_ship.getScale().x,
		m_sprite_ship.getTexture()->getSize().y * m_sprite_ship.getScale().y);

	//Center the player on the screen
	m_shipPosition.first -= m_shipSize.first / 2;
	m_shipPosition.second -= m_shipSize.second / 2;
	m_sprite_ship.setPosition(m_shipPosition.first, m_shipPosition.second);
}

void Player::DrawShip(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_sprite_ship);
}

void Player::MoveShip(int WINDOW_WIDTH)
{
	if (m_moveDirection != 0)
	{
		if (m_moveDirection < 0 && m_sprite_ship.getPosition().x > m_boundryOffset)
			m_sprite_ship.move(m_moveDirection * m_speed, 0);
		else if (m_moveDirection > 0 && m_sprite_ship.getPosition().x < (WINDOW_WIDTH - m_boundryOffset - m_shipSize.first))
		{
			m_sprite_ship.move(m_moveDirection * m_speed, 0);
		}
	}
}

void Player::SetMoveDirection(int direction)
{
	m_moveDirection = direction;
}