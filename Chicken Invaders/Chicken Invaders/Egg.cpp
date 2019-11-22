#include "Egg.h"

//Default constructor of the egg, it load a testure, sets the sprite's texture, scale, position and calculates the size
Egg::Egg(const std::string& path, sf::Vector2f initialPos)
{
	m_textureEgg.loadFromFile(path);
	m_spriteEgg.setTexture(m_textureEgg);

	m_spriteEgg.setScale(0.1f, 0.1f);
	m_eggSize = sf::Vector2f(m_textureEgg.getSize().x * m_spriteEgg.getScale().x, m_textureEgg.getSize().y * m_spriteEgg.getScale().y);

	initialPos.x -= m_eggSize.x / 2;
	initialPos.y -= m_eggSize.y / 2;
	m_spriteEgg.setPosition(initialPos.x, initialPos.y);
}

//Move constructor; needed for inserting (temporary) eggs into the eggs vector
Egg::Egg(Egg&& other) noexcept
{
	m_textureEgg.swap(other.m_textureEgg);
	m_spriteEgg.setTexture(m_textureEgg);

	m_spriteEgg.setScale(other.m_spriteEgg.getScale());
	m_eggSize = other.m_eggSize;
	m_spriteEgg.setPosition(other.m_spriteEgg.getPosition());
}

//Operator= needed for move constructor
Egg& Egg::operator=(const Egg& other)
{
	sf::Texture aux = other.m_textureEgg;
	m_textureEgg.swap(aux);
	m_spriteEgg.setTexture(m_textureEgg);

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