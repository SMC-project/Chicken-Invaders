#include "Player.h"

Player::Player(sf::Vector2f initialPos, const sf::Texture& texture)
{
	//Load the texture and set the sprite
	m_spriteShip.setTexture(texture);

	m_spriteShip.setTextureRect(sf::IntRect(0, 0, 256, 256));
	//Resize the sprite so that it doesn't cover too much space
	m_spriteShip.setScale(0.4f, 0.4f);
	//Retain how many pixels the ship covers because we will need it later for collision check
	//We use a sprite sheet that has more than one sprite so we divide it by how many sprotes there are on a row
	//and on col to get a single sprite's size
	sf::Vector2 texturePos(m_spriteShip.getTexture()->getSize().x / 10, m_spriteShip.getTexture()->getSize().y / 4);
	m_shipSize = sf::Vector2f(texturePos.x * m_spriteShip.getScale().x, texturePos.y * m_spriteShip.getScale().y);

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
	{
		m_movement.y = factor;
		//If we pressed right arrow set the row of the sprite sheet to the right animation
		m_animRowFrame = 2;
	}
	else
	{
		m_movement.x = -factor;
		//Otherwise set it to left only if we aren't moving right (pressing both keys)
		if(m_movement.y == 0)
			m_animRowFrame = 3;
	}

	//If we released a key
	if (factor == 0)
	{
		//If we reset both keys set the animation to idle
		if(m_movement.x == 0 && m_movement.y == 0)
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

//Load lives sprites, scale the accordingly and set their position
void Player::LoadLiveSprites(const sf::Texture& texture)
{
	for (int index = 0; index < 3; index++)
	{
		m_spriteLives[index].setTexture(texture);

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
bool Player::CheckCollision(sf::Vector2f upperLeft, sf::Vector2f size)
{
	//Check if the collision object is too far on the right or on the left of our sprite, if so we can't collide
	if (m_spriteShip.getPosition().x > (upperLeft.x + size.x) || upperLeft.x > (m_spriteShip.getPosition().x + m_shipSize.x))
		return false;

	//Check if the collision object is higher or lower than our sprite, if so we can't collide
	if (m_spriteShip.getPosition().y > (upperLeft.y + size.y) || upperLeft.y > (m_spriteShip.getPosition().y + m_shipSize.y))
		return false;

	//If it is not outside our sprite then we are overlapping with it
	return true;
}

//Decrement lives and reset position; in the future it will have a GameOver functionality
void Player::Die()
{
	m_lives--;
	m_spriteShip.setPosition(m_initialPos);

	if (m_lives == 0)
	{
		m_lives = 3;
		ResetScore();
	}
}

//Load the font for the text and set up the text's position, size, initial value.
void Player::SetUpScore(const sf::Font& font)
{
	m_scoreText.setFont(font);
	m_scoreText.setPosition(m_spriteLives[2].getPosition().x + 100, 20);
	m_scoreText.setString(std::to_string(m_score));
}
//Add to the score, called when defeating an enemy
void Player::UpdateScore(int value)
{
	m_score += value;
}
//Reset the score, called when the player reaches 0 lives
void Player::ResetScore()
{
	m_score = 0;
}

//Draw the score to the screen
void Player::DrawScore(sf::RenderWindow& window)
{
	m_scoreText.setString(std::to_string(m_score));
	window.draw(m_scoreText);
}

//Will change the rect of the spritesheet to simulate an animation
//It knows which rect to pick so that it renders the expected animation
void Player::Animate()
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
	m_spriteShip.setTextureRect(sf::IntRect(m_animColFrame * 256, 256 * m_animRowFrame, 256, 256));
}

sf::Vector2f Player::GetPosition() { return m_spriteShip.getPosition(); }