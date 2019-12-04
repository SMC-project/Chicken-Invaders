#include "Egg.h"

//Default constructor of the egg, it load a testure, sets the sprite's texture, scale, position and calculates the size
Egg::Egg(sf::Vector2f initialPos, const sf::Texture& texture)
{
	m_spriteEgg.setTexture(texture);

	m_spriteEgg.setScale(0.1f, 0.1f);
	m_eggSize = sf::Vector2f(texture.getSize().x * m_spriteEgg.getScale().x, texture.getSize().y * m_spriteEgg.getScale().y);

	m_speed = rand() % 10 + 5;

	initialPos.x -= m_eggSize.x / 2;
	initialPos.y -= m_eggSize.y / 2;
	m_spriteEgg.setPosition(initialPos.x, initialPos.y);
}

//Move constructor; needed for inserting (temporary) eggs into the eggs vector
Egg::Egg(Egg&& other) noexcept
{
	m_spriteEgg.setTexture(*other.m_spriteEgg.getTexture());

	m_spriteEgg.setScale(other.m_spriteEgg.getScale());
	m_eggSize = other.m_eggSize;
	m_spriteEgg.setPosition(other.m_spriteEgg.getPosition());
}

//Operator= needed for move constructor
Egg& Egg::operator=(const Egg& other)
{
	m_spriteEgg.setTexture(*other.m_spriteEgg.getTexture());

	m_spriteEgg.setScale(other.m_spriteEgg.getScale());
	m_eggSize = other.m_eggSize;
	m_spriteEgg.setPosition(other.m_spriteEgg.getPosition());
	return *this;
}

//Move the egg downwards and return true if it exits the screen
bool Egg::FallDown(int screenHeight)
{
	m_spriteEgg.move(0, m_speed);

	if (m_spriteEgg.getPosition().y > screenHeight)
		return true;
	return false;
}

void Egg::DrawEgg(sf::RenderWindow& window)
{
	window.draw(m_spriteEgg);
}

sf::Vector2f Egg::GetPosition() { return m_spriteEgg.getPosition(); }
sf::Vector2f Egg::GetSize() { return m_eggSize; }