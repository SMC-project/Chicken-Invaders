#include "Meat.h"

Meat::Meat(sf::Vector2f initialPos, const sf::Texture& texture)
{
	m_sprite.setTexture(texture);

	m_sprite.setScale(0.15f, 0.15f);
	m_size = sf::Vector2f(texture.getSize().x * m_sprite.getScale().x, texture.getSize().y * m_sprite.getScale().y);

	initialPos.x -= m_size.x / 2;
	initialPos.y -= m_size.y / 2;
	m_sprite.setPosition(initialPos.x, initialPos.y);
}

//Move constructor; needed for inserting (temporary) eggs into the eggs vector
Meat::Meat(Meat&& other) noexcept
{
	m_sprite.setTexture(*other.m_sprite.getTexture());

	m_sprite.setScale(other.m_sprite.getScale());
	m_size = other.m_size;
	m_sprite.setPosition(other.m_sprite.getPosition());
}

//Operator= needed for move constructor
Meat& Meat::operator=(const Meat& other)
{
	m_sprite.setTexture(*other.m_sprite.getTexture());

	m_sprite.setScale(other.m_sprite.getScale());
	m_size = other.m_size;
	m_sprite.setPosition(other.m_sprite.getPosition());
	return *this;
}


bool Meat::Move()
{
	return false;
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
