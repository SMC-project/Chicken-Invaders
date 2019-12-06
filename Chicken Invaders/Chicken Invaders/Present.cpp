#include "Present.h"


Present::Present(sf::Vector2f initialPos, const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(.15, .15);
	m_sprite.setPosition(initialPos.x, initialPos.y);
}

Present::Present(Present&& other) noexcept
{
	m_sprite.setTexture(*other.m_sprite.getTexture());
	m_sprite.scale(other.m_sprite.getScale());
	m_sprite.setPosition(other.m_sprite.getPosition());
}

Present& Present::operator=(const Present& other)
{
	m_sprite.setTexture(*other.m_sprite.getTexture());
	m_sprite.scale(other.m_sprite.getScale());
	m_sprite.setPosition(other.m_sprite.getPosition());
	return *this;
}

void Present::DropPresent()
{
	m_framePresent += m_animSpeed_Present;
	if (m_framePresent > m_frameCountPresent) m_framePresent = 0;
	m_sprite.setTextureRect(IntRect(int(m_framePresent) * 256, 0, 256, 256));
}

void Present::SetSpritePresent(const Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale(.15, .15);
}

void Present::DrawPresent(RenderWindow& map)
{
	DropPresent();
	map.draw(m_sprite);
}

void Present::SetPositionPresent(float posX, float posY)
{
	m_sprite.setPosition(posX, posY);
}

bool Present::FallDownPresent(int windowHeight)
{
	m_sprite.move(0, m_fallDownSpeed);
	if (m_sprite.getPosition().y > windowHeight)
		return true;
	return false;
}

const sf::Sprite& Present::GetSprite() { return m_sprite; }

