#include "Player.h"

void Player::Init(sf::Vector2f initialPos, const sf::Texture& texture, const sf::Texture& uiMissileTexture)
{
	//Load the texture and set the sprite
	m_spriteShip.setTexture(texture);

	m_spriteShip.setTextureRect(sf::IntRect(0, 0, 256, 256));
	//Resize the sprite so that it doesn't cover too much space
	m_spriteShip.setScale(0.4f, 0.4f);
	//Retain how many pixels the ship covers because we will need it later for collision check
	//We use a sprite sheet that has more than one sprite so we divide it by how many sprotes there are on a row
	//and on col to get a single sprite's size
	sf::Vector2f texturePos(m_spriteShip.getTexture()->getSize().x / 10, m_spriteShip.getTexture()->getSize().y / 4);
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

	m_ui_rocket.setTexture(uiMissileTexture);
	m_ui_rocket.setScale(0.25, 0.25);
}

void Player::AddMeat()
{
	m_currentMeat++;
	m_nrMissiles = m_currentMeat / m_meatNeededForRocket;
}

void Player::DrawUIMissile(sf::RenderWindow& gameWindow, const sf::Texture& texture)
{
	m_ui_rocket.setPosition(-20, 1010);
	for (int i = 0; i < m_nrMissiles; i++)
	{
		m_ui_rocket.move(25, 0);
		gameWindow.draw(m_ui_rocket);
	}
}

//Draw the sprite to the window, it may be more complex in the future (with animations) so I made it a method.
void Player::DrawShip(sf::RenderWindow& gameWindow, float deltaTimeSeconds)
{
	//If we are immortal then we want to make a blinking animation
	if (m_isImmortal == true)
	{
		//If we just died and became immortal then retain how long we will be immortal for
		if (m_currentImmortalTime == 0)
			m_currentImmortalTime = m_maxImmortalTime;

		//Decrement the deltaTime to know how much time has passed
		m_currentImmortalTime -= deltaTimeSeconds;

		//If the current immortal time is less then 0 then we will stop being immortal
		if (m_currentImmortalTime < 0)
		{
			m_currentImmortalTime = 0;
			m_isImmortal = false;
		}

		//Make the blinking animation only at certain times
		if ((m_currentImmortalTime >= 1.9f && m_currentImmortalTime <= 2.1f) ||
			(m_currentImmortalTime >= 1.4f && m_currentImmortalTime <= 1.6f) ||
			(m_currentImmortalTime >= 0.9f && m_currentImmortalTime <= 1.1f) ||
			(m_currentImmortalTime >= 0.4f && m_currentImmortalTime <= 0.6f))
		{
			gameWindow.draw(m_spriteShip);
		}
	}
	else
	{
		gameWindow.draw(m_spriteShip);
	}
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

//Decrement lives and reset position; in the future it will have a GameOver functionality
void Player::Die()
{
	m_isImmortal = true;
	m_lives--;
	m_spriteShip.setPosition(m_initialPos);
}
bool Player::IsImmortal() 
{ 
	return m_isImmortal; 
}

void Player::Reset()
{
	m_lives = 3;
	m_score = 0;
	m_spriteShip.setPosition(m_initialPos);
	m_currentMeat = 0;
	m_nrMissiles = 0;
	m_currentImmortalTime = 0;
	m_isImmortal = false;
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
int Player::GetNrMissiles() { return m_nrMissiles; }
void Player::ShootMissile() 
{
	m_nrMissiles--;
	m_currentMeat-=25; 
}

const sf::Sprite& Player::GetSprite() { return m_spriteShip; }
bool Player::IsDead() { return m_lives == 0 ? true : false; }
uint32_t Player::GetScore() { return m_score; }

const sf::Vector2f& Player::GetSize() { return m_shipSize; }

int Player::GetLifes(){	return m_lives; }
