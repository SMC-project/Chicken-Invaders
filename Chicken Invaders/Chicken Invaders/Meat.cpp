#include "Meat.h"
#include <math.h>
#include <iostream>

Meat::Meat(sf::Vector2f initialPos, const sf::Texture& texture)
{
	m_sprite.setTexture(texture);

	m_sprite.setScale(0.15f, 0.15f);
	m_size = sf::Vector2f(texture.getSize().x * m_sprite.getScale().x, texture.getSize().y * m_sprite.getScale().y);

	initialPos.x -= m_size.x / 2;
	initialPos.y -= m_size.y / 2;
	m_sprite.setPosition(initialPos.x, initialPos.y);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height/2);

	int random = rand() % 360;
	if (rand() % 2 == 1)
	{
		random = -random;
		m_rotationFact = -1;
	}
	m_sprite.setRotation(random);
	m_rotationSpeed = rand() % 5 + 5;

	m_velocity.x = rand() % 8+2;
	if (rand() % 2 == 1)
		m_velocity.x = -m_velocity.x;

	m_velocity.y = -(rand() % 5);
	m_destroyTime = 10;
}
//Move constructor; needed for inserting (temporary) eggs into the eggs vector
Meat::Meat(Meat&& other) noexcept
{
	m_sprite.setTexture(*other.m_sprite.getTexture());

	m_sprite.setScale(other.m_sprite.getScale());
	m_sprite.setRotation(other.m_sprite.getRotation());
	m_size = other.m_size;
	m_sprite.setPosition(other.m_sprite.getPosition());
	m_sprite.setOrigin(other.m_sprite.getOrigin());

	m_velocity = other.m_velocity;
	m_destroyTime = other.m_destroyTime;
	m_rotationFact = other.m_rotationFact;
	m_rotationSpeed = other.m_rotationSpeed;
}

//Operator= needed for move constructor
Meat& Meat::operator=(const Meat& other)
{
	m_sprite.setTexture(*other.m_sprite.getTexture());

	m_sprite.setScale(other.m_sprite.getScale());
	m_sprite.setRotation(other.m_sprite.getRotation());
	m_size = other.m_size;
	m_sprite.setPosition(other.m_sprite.getPosition());
	m_sprite.setOrigin(other.m_sprite.getOrigin());

	m_velocity = other.m_velocity;
	m_destroyTime = other.m_destroyTime;
	m_rotationFact = other.m_rotationFact;
	m_rotationSpeed = other.m_rotationSpeed;

	return *this;
}

//returns false when the object can't move anymore
bool Meat::Move(int SCREEN_WIDTH, int SCREEN_HEIGHT, float deltaTimeSeconds)
{
	m_velocity.y += m_accelerationFact;

	m_sprite.rotate(m_rotationFact * m_rotationSpeed);
	
	//When we are bouncing we set m_bounce and m_sideBounce so that we don't bounce multiple times in consecutive frames
	//It happens when an object had too much speed and goes too far sideways or downwards
	if (m_bounce > 0)
	{
		//We subtract the deltaTime so that afer a small number of seconds we can bounce again
		m_bounce -= deltaTimeSeconds;
		if (m_bounce < 0)
			m_bounce = 0;
	}
	if (m_sideBounce > 0)
	{
		m_sideBounce -= deltaTimeSeconds;
		if (m_sideBounce < 0)
			m_sideBounce = 0;
	}

	//Decrease the acceleration on the x axis
	if (m_velocity.x < 0)
	{
		m_velocity.x += m_accelerationFact / 2;
		if (m_velocity.x > 0)
			m_velocity.x = 0;
	}
	if (m_velocity.x > 0)
	{
		m_velocity.x -= m_accelerationFact / 2;
		if (m_velocity.x < 0)
			m_velocity.x = 0;
	}

	//If we hit the side boundry of the screen we want to bounce back
	if (m_sideBounce == 0 && (m_sprite.getPosition().x < 10 || m_sprite.getPosition().x > SCREEN_WIDTH - m_size.x - 10))
	{
		//So we reverse the movement direction
		m_velocity.x = -m_velocity.x;
		//And set the bounce variable so we don't bounce again
		m_sideBounce = 0.1f;
	}
	//Same forr the bottom of the screen bounce
	if (m_bounce == 0 && m_sprite.getPosition().y > SCREEN_HEIGHT - m_size.y - 10)
	{
		//But here we decrease the velocity
		m_velocity.y = -m_velocity.y / (3 + rand() % 3);
		m_bounce = 0.1f;
	}

	//It's finally time to move the sprite
	m_sprite.move(m_velocity.x, m_velocity.y);

	m_destroyTime -= deltaTimeSeconds;
	//If the time has passed, destroy the object
	if (m_destroyTime < 0)
		return false;

	return true;
}

void Meat::Draw(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_sprite);
}

sf::Vector2f Meat::GetPosition()
{
	return sf::Vector2f();
}

sf::Vector2f Meat::GetSize()
{
	return sf::Vector2f();
}

const sf::Sprite& Meat::GetSprite() { return m_sprite; }