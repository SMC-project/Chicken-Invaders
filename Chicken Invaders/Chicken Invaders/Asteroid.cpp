#include "Asteroid.h"


Asteroid::Asteroid(sf::Vector2f initialPos, const sf::Texture& texture)
{
	m_sprite_asteroid.setTexture(texture);
	m_sprite_asteroid.setScale(.2, .2);
	m_sprite_asteroid.setRotation(-45);
	m_asteroidSize = Vector2f(256 * m_sprite_asteroid.getScale().x, 1024 * m_sprite_asteroid.getScale().y);

	initialPos.x -= m_asteroidSize.x / 2;
	initialPos.y -= m_asteroidSize.y / 2;
	m_sprite_asteroid.setPosition(initialPos.x, initialPos.y);
}

Asteroid::Asteroid(Asteroid&& other) noexcept
{
	m_sprite_asteroid.setTexture(*other.m_sprite_asteroid.getTexture());

	m_sprite_asteroid.setScale(other.m_sprite_asteroid.getScale());
	m_asteroidSize = other.m_asteroidSize;
	m_sprite_asteroid.setPosition(other.m_sprite_asteroid.getPosition());
}

Asteroid& Asteroid::operator=(const Asteroid& other)
{
	m_sprite_asteroid.setTexture(*other.m_sprite_asteroid.getTexture());

	m_sprite_asteroid.setScale(other.m_sprite_asteroid.getScale());
	m_asteroidSize = other.m_asteroidSize;
	m_sprite_asteroid.setPosition(other.m_sprite_asteroid.getPosition());
	return *this;
}


void Asteroid::Asteroid_animation()
{
	frame_asteroid1 += animSpeed_Asteroid1;
	if (frame_asteroid1 > framecount_asteroid1) 
		frame_asteroid1 = 0;
	m_sprite_asteroid.setTextureRect(IntRect(int(frame_asteroid1) * 256, 0, 256, 1024));
}

void Asteroid::draw_asteroid(RenderWindow& map)
{
	Asteroid_animation();
	map.draw(m_sprite_asteroid);
}

void Asteroid::asteroid_setPosition(float x_POS, float y_POS)
{
	m_sprite_asteroid.setPosition(x_POS, y_POS);
	m_sprite_asteroid.setRotation(-45);
}

bool Asteroid::Falldown(int screenHeight)
{
	m_sprite_asteroid.move(10,10);

	if (m_sprite_asteroid.getPosition().y > screenHeight)
		return true;
	return false;
}

Vector2f Asteroid::GetPosition() { return m_sprite_asteroid.getPosition(); }
Vector2f Asteroid::GetSize() { return m_asteroidSize; }
