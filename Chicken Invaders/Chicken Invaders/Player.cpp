#include "Player.h"

Player::Player(const std::string& spritePath, sf::Vector2<int> initialPos)
{
	//Load the texture and set the sprite
	m_textureShip.loadFromFile(spritePath);
	m_spriteShip.setTexture(m_textureShip);

	//Resize the sprite so that it doesn't cover too much space
	m_spriteShip.setScale(0.15f, 0.15f);
	//Retain how many pixels the ship covers because we will need it later for collision check
	m_shipSize = sf::Vector2(static_cast<int>(m_spriteShip.getTexture()->getSize().x * m_spriteShip.getScale().x),
		static_cast<int>(m_spriteShip.getTexture()->getSize().y * m_spriteShip.getScale().y));

	//Center the player on the screen
	initialPos.x -= m_shipSize.x / 2;
	initialPos.y -= m_shipSize.y / 2;
	m_spriteShip.setPosition(initialPos.x, initialPos.y);

	//Retain the initial position; used for resetting the player when he dies
	m_initialPos.x = initialPos.x;
	m_initialPos.y = initialPos.y;

	//Set default values
	m_movement.x = 0;
	m_movement.y = 0;
}

//Draw the sprite to the window, it may be more complex in the future (with animations) so I made it a method.
void Player::DrawShip(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_spriteShip);
}

//Move the ship, if you don't understand the code look at 'm_movement' description
void Player::MoveShip(int WINDOW_WIDTH)
{
	//Right arrow has priority in movement
	int moveDirection = m_movement.y;
	//If we didn't press the right arrow try looking for the first arrow
	if (moveDirection == 0)
		moveDirection = m_movement.x;

	if (moveDirection != 0)
	{
		//If we try to move left then we need to check to not pass the boundry so that we don't exit the screen
		if (moveDirection < 0 && m_spriteShip.getPosition().x > m_boundryOffset)
			m_spriteShip.move(moveDirection * m_speed, 0);
		//If we try to move right then we need to check to not pass the boundry so that we don't exit the screen
		else if (moveDirection > 0 && m_spriteShip.getPosition().x < (WINDOW_WIDTH - m_boundryOffset - m_shipSize.x))
		{
			//The movement is relative to the last position of the sprite, so we can use a direction and a speed for it and not real coordinates
			m_spriteShip.move(moveDirection * m_speed, 0);
		}
	}
}

//Move right is used to know which value to set in the movement vector and the factor for how much to move (max value of 1)
//For a more detalied explanation check 'm_movement' description
void Player::SetMovement(bool moveRight, float factor)
{
	if (moveRight)
		m_movement.y = factor;
	else
		m_movement.x = -factor;
}

//Load lives sprites, scale the accordingly and set their position
void Player::LoadLiveSprites(const std::string& livesSpritePath)
{
	for (int index = 0; index < 3; index++)
	{
		m_textureLives[index].loadFromFile(livesSpritePath);
		m_spriteLives[index].setTexture(m_textureLives[0]);

		m_spriteLives[index].setScale(0.05f, 0.05f);
		m_spriteLives[index].setPosition(15 + index * m_spriteLives[index].getTexture()->getSize().x * m_spriteLives[index].getScale().x, 15);
	}
}
void Player::DrawLives(sf::RenderWindow& gameWindow)
{
	//Draw only how many lives we have left on the screen
	for (int index = 0; index < m_lives; index++)
		gameWindow.draw(m_spriteLives[index]);
}

//Check if we collided with something; to do this we check the upper left corner and lower right corner of the sprites
bool Player::CheckCollision(sf::Vector2<float> upperLeft, sf::Vector2<int> lowerRight)
{
	//Check if the collision object is too far on the right or on the left of our sprite, if so we can't collide
	if (m_spriteShip.getPosition().x > lowerRight.x || upperLeft.x > m_shipSize.x)
		return false;

	//Check if the collision object is higher or lower than our sprite, if so we can't collide
	if (m_spriteShip.getPosition().y < lowerRight.y || upperLeft.y < m_shipSize.y)
		return false;

	//If it is not outside our sprite then we are overlapping with it
	return true;
}

//Decrement lives and reset position; in the future it will have a GameOver functionality
void Player::Die()
{
	m_lives--;
	m_spriteShip.setPosition(m_initialPos);
}
