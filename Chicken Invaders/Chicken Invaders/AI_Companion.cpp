#include "AI_Companion.h"
void AI_Companion::Init(sf::Vector2f initialPos, const sf::Texture& texture)
{
	//Load the texture and set the sprite
	m_sprite.setTexture(texture);

	m_sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
	//Resize the sprite so that it doesn't cover too much space
	m_sprite.setScale(0.3f, 0.3f);
	//Retain how many pixels the ship covers because we will need it later for collision check
	//We use a sprite sheet that has more than one sprite so we divide it by how many sprotes there are on a row
	//and on col to get a single sprite's size
	sf::Vector2 texturePos(m_sprite.getTexture()->getSize().x / 10, m_sprite.getTexture()->getSize().y / 4);
	m_size = sf::Vector2f(texturePos.x * m_sprite.getScale().x, texturePos.y * m_sprite.getScale().y);

	//Center the player on the screen
	initialPos.x -= m_size.x / 2 - 100;
	initialPos.y -= m_size.y / 2;
	m_sprite.setPosition(initialPos.x, initialPos.y);

	//Retain the initial position; used for resetting the player when he dies
	m_initialPos.x = initialPos.x;
	m_initialPos.y = initialPos.y;

	//Set default values
	m_movement.x = 0;
	m_movement.y = 0;


}

void AI_Companion::DrawShip(sf::RenderWindow& gameWindow)
{
	if (m_active == true)
		gameWindow.draw(m_sprite);
}

void AI_Companion::MoveShip(int WINDOW_WIDTH, sf::Vector2f shipPosition, sf::Vector2f shipSize)
{
	int addRight = 0;
	int addLeft = 0;
	if (m_rotateRight == false)
	{
		addLeft = 210;
		addRight = 0;
	}
	else
	{
		addLeft = 0;
		addRight = -210;
	}
	if (m_active == true)
	{
		//Right arrow has priority in movement
		int moveDirection = m_movement.y;
		//If we didn't press the right arrow try looking for the first arrow
		if (moveDirection == 0)
			moveDirection = m_movement.x;

		if (moveDirection != 0)
		{
			//If we try to move left then we need to check to not pass the boundry so that we don't exit the screen
			if (moveDirection < 0 && m_sprite.getPosition().x > m_boundryOffset + addLeft)
				m_sprite.move(moveDirection * m_speed, 0);
			//If we try to move right then we need to check to not pass the boundry so that we don't exit the screen
			else if (moveDirection > 0 && m_sprite.getPosition().x <= (WINDOW_WIDTH - m_boundryOffset - m_size.x) + addRight)
			{
				//The movement is relative to the last position of the sprite, so we can use a direction and a speed for it and not real coordinates
				m_sprite.move(moveDirection * m_speed, 0);
			}
			if (moveDirection < 0 && m_sprite.getPosition().x < m_boundryOffset)
				m_startRotation = true;
			if (moveDirection > 0 && m_sprite.getPosition().x >= (WINDOW_WIDTH - m_boundryOffset - m_size.x))
				m_startRotation = true;
		}
		if (m_startRotation == true)
		{
			if (m_rotateRight == true)
				m_angle += 5;
			else
				m_angle -= 5;
			if (m_angle >= 185)
			{
				m_rotateRight = false;
				m_startRotation = false;
			}
			if (m_angle <= -3)
			{
				m_rotateRight = true;
				m_startRotation = false;
			}

			//xPos = (cos(m_angle) * (m_sprite.getPosition().x - shipPosition.x) - sin(m_angle) * (m_sprite.getPosition().y - shipPosition.y) + shipPosition.x);
			//yPos = (sin(m_angle) * (m_sprite.getPosition().x - shipPosition.x) + cos(m_angle) * (m_sprite.getPosition().y - shipPosition.y) + shipPosition.y);
			xPos = shipPosition.x + 10 + (cos(m_angle * pi / 180) * -m_radius);
			yPos = shipPosition.y + 10 + (sin(m_angle * pi / 180) * -m_radius);
			m_sprite.setPosition(xPos, yPos);

		}
	}
}

void AI_Companion::SetMovement(bool moveRight, float factor)
{
	if (m_active == true)
	{
		if (moveRight)
		{
			m_movement.y = factor;
			//If we pressed right arrow set the row of the sprite sheet to the right animation
			m_animRowFrame = 2;
		}
		else
		{
			m_movement.x = -factor;
			//Otherwise set it to left only if we aren't moving right (pressing both keys)
			if (m_movement.y == 0)
				m_animRowFrame = 3;
		}

		//If we released a key
		if (factor == 0)
		{
			//If we reset both keys set the animation to idle
			if (m_movement.x == 0 && m_movement.y == 0)
				m_animRowFrame = 0;
			else
			{
				//Otherwise change it to right or left animation
				if (m_movement.x < 0)
					m_animRowFrame = 3;
				if (m_movement.y > 0)
					m_animRowFrame = 2;
			}
		}
	}
}

void AI_Companion::Animate()
{
	if (m_active == true)
	{
		//Increase the index of the current animation
		m_animColFrame++;
		if (m_animRowFrame == 2 || m_animRowFrame == 3)
		{
			//If it is a move animation we want to stop at the 5th frame (starts from 0)
			if (m_animColFrame > 4)
				m_animColFrame = 4;
		}
		else
		{
			//Otherwise if it is idle toggle between entire row
			if (m_animColFrame == 9)
				m_animColFrame = 0;
		}
		//Select the rect to render
		m_sprite.setTextureRect(sf::IntRect(m_animColFrame * 256, 256 * m_animRowFrame, 256, 256));
	}
}

const sf::Vector2f& AI_Companion::GetPosition() { return m_sprite.getPosition(); }

bool AI_Companion::Shoot(std::vector<Chicken>& chickens, std::vector<Asteroid>& asteroids, std::vector<Boss>& boss, Clock& clock)
{
	if (m_active == true)
	{
		if (clock.getElapsedTime().asSeconds() - m_lastBullet > 5)
		{
			//Chickens
			for (int i=chickens.size()-1; i >=0; i--)
				if (abs(chickens[i].getPosition().y - m_sprite.getPosition().y) < 700)
				{
					if (chickens[i].getPosition().x - m_sprite.getPosition().x < 60 && chickens[i].getPosition().x - m_sprite.getPosition().x>0 && chickens[i].IsMovingRight() == true)
					{
						m_lastBullet = clock.getElapsedTime().asSeconds();
						return true;
					}
					if (chickens[i].getPosition().x - m_sprite.getPosition().x < 0 &&chickens[i].getPosition().x - m_sprite.getPosition().x >-60 && chickens[i].IsMovingRight() == false)
					{
						m_lastBullet = clock.getElapsedTime().asSeconds();
						return true;
					}

				}
				else if (abs(chickens[i].getPosition().y - m_sprite.getPosition().y) < 1080)
				{
					if (chickens[i].getPosition().x - m_sprite.getPosition().x < 180 && chickens[i].getPosition().x - m_sprite.getPosition().x>0 && chickens[i].IsMovingRight() == true)
					{
						m_lastBullet = clock.getElapsedTime().asSeconds();
						return true;
					}
					if (chickens[i].getPosition().x - m_sprite.getPosition().x < 0 && chickens[i].getPosition().x - m_sprite.getPosition().x >-180 && chickens[i].IsMovingRight() == false)
					{
						m_lastBullet = clock.getElapsedTime().asSeconds();
						return true;
					}
				}
				
		//Asteroids
			for (int i = 0; i < asteroids.size(); i++)
				if (abs(asteroids[i].GetPosition().x - m_sprite.getPosition().x < 250))
				{
					m_lastBullet = clock.getElapsedTime().asSeconds();
					return true;
				}
			//GameBosses
			for (int i = 0; i < boss.size(); i++)
			{
					if (boss[i].GetPosition().x - m_sprite.getPosition().x < 60 && boss[i].GetPosition().x - m_sprite.getPosition().x>0 && boss[i].IsMovingRight() == false)
					{
						m_lastBullet = clock.getElapsedTime().asSeconds();
						return true;
					}
					if (boss[i].GetPosition().x - m_sprite.getPosition().x < 0 && boss[i].GetPosition().x - m_sprite.getPosition().x >-60 && boss[i].IsMovingRight() == true)
					{
						m_lastBullet = clock.getElapsedTime().asSeconds();
						return true;
					}

			}
		}
	}
	return false;
}



void AI_Companion::ChangeActiveValue()
{
	if (m_active == true)
		m_active = false;
	else
		m_active = true;
}

void AI_Companion::SetActive()
{
	m_active = true;
}

void AI_Companion::SetInactive()
{
	m_active = false;
}

void AI_Companion::SetPosition(Player& player)
{

	m_sprite.setPosition(player.GetPosition().x + 115, player.GetPosition().y+15);
}

bool AI_Companion::GetActivated()
{
	return m_activated;
}

void AI_Companion::ChangeActivatedValue()
{
	if (m_activated == true)
		m_activated = false;
	else
		m_activated = true;
}

void AI_Companion::Reset()
{
	//Is active in game
	m_active = false;

	//Special Rotation
	m_startRotation = false;
	m_rotateRight = false;
	m_activated = false;
}



