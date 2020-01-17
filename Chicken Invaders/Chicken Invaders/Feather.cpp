#include "Feather.h"

Feather::Feather(sf::Vector2f initialPos, const sf::Texture& texture)
{
	m_sprite.setTexture(texture);

	m_sprite.setScale(0.15f, 0.15f);
	m_size = sf::Vector2f(texture.getSize().x * m_sprite.getScale().x, texture.getSize().y * m_sprite.getScale().y);

	initialPos.x -= m_size.x / 2;
	initialPos.y -= m_size.y / 2;
	m_sprite.setPosition(initialPos.x, initialPos.y);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	int random = rand() % 360;
	if (rand() % 2 == 1)
	{
		random = -random;
		m_rotationFact = -1;
	}
	m_sprite.setRotation(random);
	m_rotationSpeed = rand() % 5 + 5;
	m_velocity.x = rand() % 8 + 2;
	if (rand() % 2 == 1)
		m_velocity.x = -m_velocity.x;

	m_velocity.y = -(rand() % 5);
	m_destroyTime = 10;

}

Feather::Feather(Feather&& other) noexcept
{
	m_sprite.setTexture(*other.m_sprite.getTexture());

	m_sprite.setScale(other.m_sprite.getScale());
	m_sprite.setRotation(other.m_sprite.getRotation());
	m_size = other.m_size;
	m_sprite.setPosition(other.m_sprite.getPosition());
	m_sprite.setOrigin(other.m_sprite.getOrigin());
	m_destroyTime = other.m_destroyTime;
	m_velocity = other.m_velocity;
	m_rotationFact = other.m_rotationFact;
	m_rotationSpeed = other.m_rotationSpeed;

	

}

Feather& Feather::operator=(const Feather&& other) noexcept
{
	m_sprite.setTexture(*other.m_sprite.getTexture());

	m_sprite.setScale(other.m_sprite.getScale());
	m_sprite.setRotation(other.m_sprite.getRotation());
	m_size = other.m_size;
	m_sprite.setPosition(other.m_sprite.getPosition());
	m_sprite.setOrigin(other.m_sprite.getOrigin());
	m_destroyTime = other.m_destroyTime;
	m_velocity = other.m_velocity;
	m_rotationFact = other.m_rotationFact;
	m_rotationSpeed = other.m_rotationSpeed;

	return *this;
}

bool Feather::Move(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT, float deltaTimeSeconds)
{
	m_velocity.y += m_accelerationFact;

	m_sprite.rotate(m_rotationFact * m_rotationSpeed);

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


	// Move the sprite
	m_sprite.move(m_velocity.x, m_velocity.y);
	m_destroyTime -= deltaTimeSeconds;

	//If the time has passed, destroy the object
	if (m_destroyTime < 0)
		return false;

	return true;
}

void Feather::Draw(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_sprite);
}

