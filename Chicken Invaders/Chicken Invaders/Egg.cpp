#include "Egg.h"

Egg::Egg(const std::string& path, sf::Vector2<int> initialPos)
{
	m_textureEgg.loadFromFile(path);
	m_spriteEgg.setTexture(m_textureEgg);

	m_spriteEgg.setScale(0.1f, 0.1f);
	m_eggSize = sf::Vector2<int>(m_textureEgg.getSize().x * m_spriteEgg.getScale().x, m_textureEgg.getSize().y * m_spriteEgg.getScale().y);

	initialPos.x -= m_eggSize.x / 2;
	initialPos.y -= m_eggSize.y / 2;
	m_spriteEgg.setPosition(initialPos.x, initialPos.y);
}

void Egg::FallDown()
{
}

void Egg::DrawEgg(sf::RenderWindow& window)
{
	window.draw(m_spriteEgg);
}

void Egg::CheckBounds(const sf::RenderWindow& window)
{
}
