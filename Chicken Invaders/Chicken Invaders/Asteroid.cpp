#include "Asteroid.h"


Asteroid::Asteroid(sf::Vector2f initialPos, const sf::Texture& texture)
{
	m_sprite_asteroid.setTexture(texture);
	m_sprite_asteroid.setScale(.2, .2);
	m_asteroidSize = Vector2f(256 * m_sprite_asteroid.getScale().x, 1024 * m_sprite_asteroid.getScale().y);
	initialPos.x -= m_asteroidSize.x / 2;
	initialPos.y -= m_asteroidSize.y / 2;
	m_sprite_asteroid.setPosition(initialPos.x, initialPos.y);
	hits_remaining = 1;

}

Asteroid::Asteroid(Asteroid&& other) noexcept
{
	m_sprite_asteroid.setTexture(*other.m_sprite_asteroid.getTexture());

	m_sprite_asteroid.setScale(other.m_sprite_asteroid.getScale());
	m_asteroidSize = other.m_asteroidSize;
	m_sprite_asteroid.setPosition(other.m_sprite_asteroid.getPosition());
	hits_remaining = other.hits_remaining;
	frame_asteroid1 = other.frame_asteroid1;
	framecount_asteroid1 = other.framecount_asteroid1;
	animSpeed_Asteroid1 = other.animSpeed_Asteroid1;
	m_sprite_asteroid.setRotation(other.m_sprite_asteroid.getRotation());
	m_velocity = other.m_velocity;
}

Asteroid& Asteroid::operator=(const Asteroid& other)
{
	m_sprite_asteroid.setTexture(*other.m_sprite_asteroid.getTexture());

	m_sprite_asteroid.setScale(other.m_sprite_asteroid.getScale());
	m_asteroidSize = other.m_asteroidSize;
	m_sprite_asteroid.setPosition(other.m_sprite_asteroid.getPosition());
	hits_remaining = other.hits_remaining;
	frame_asteroid1 = other.frame_asteroid1;
	framecount_asteroid1 = other.framecount_asteroid1;
	animSpeed_Asteroid1 = other.animSpeed_Asteroid1;
	m_sprite_asteroid.setRotation(other.m_sprite_asteroid.getRotation());
	m_velocity = other.m_velocity;
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
	//m_sprite_asteroid.setRotation(-45);
}

bool Asteroid::Falldown(int screenHeight, float posX, float posY)
{
	m_sprite_asteroid.move(posX, posY);

	if (m_sprite_asteroid.getPosition().y > screenHeight)
		return true;
	return false;
}

void Asteroid::setRotation(float rotation)
{
	m_sprite_asteroid.setRotation(rotation);
}

float Asteroid::getVelocity()
{
	return m_velocity;
}

void Asteroid::setVelocity(float velocity)
{
	m_velocity = velocity;
}

float Asteroid::getScore()
{
	return m_score;
}

void Asteroid::SetHits_Remaining(int number)
{
	hits_remaining = number;
}

int Asteroid::GetHits_Remaining()
{
	return hits_remaining;
}

Vector2f Asteroid::GetPosition() {

	Vector2f temp(m_sprite_asteroid.getPosition().x, m_sprite_asteroid.getPosition().y);
	if (m_sprite_asteroid.getRotation() == 0)
	{
		temp.x -= 45;
		temp.y += 115;
		std::cout << "mamamamama";
	}
	if (m_sprite_asteroid.getRotation() == 45)
	{
		//std::cout << "da0";
		//temp.x+=300;
		//temp.y -= 90;
	}
	if(m_sprite_asteroid.getRotation()==315)
	{
		std::cout << "da1";
		temp.x +=70;
		temp.y+=10;
	}
	return temp;

}
Vector2f Asteroid::GetSize() { return m_asteroidSize; }

const sf::Sprite& Asteroid::GetSprite() { return m_sprite_asteroid; }