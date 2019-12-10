#include "Earth.h"

void Earth::Init(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_size = sf::Vector2f(texture.getSize().x * m_sprite.getScale().x, texture.getSize().y * m_sprite.getScale().y);
}

void Earth::Move()
{
	if (m_finishMove == true)
		return;
	m_sprite.move(m_velocity * m_speed);
	
	float distance = abs(m_sprite.getPosition().x - m_targetPos.x + m_sprite.getPosition().y - m_targetPos.y);
	if (distance < 10)
	{
		m_velocity = sf::Vector2f(0, 0);
		m_finishMove = true;
	}
}

void Earth::SetPosition(sf::Vector2f initialPos)
{
	//When we initialize earth we want it to be outside the screen, so we subtract half it's height because the origin is in the center.
	initialPos.y -= m_size.y / 2;
	m_sprite.setPosition(initialPos);
}

void Earth::SetTarget(sf::Vector2f target)
{
	m_finishMove = false;
	m_targetPos = target;
	m_velocity = sf::Vector2f(target - m_sprite.getPosition());
}

void Earth::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Earth::Reset()
{
	m_finishMove = true;
	m_initWave = false;
	m_velocity = sf::Vector2f(0, 0);
	m_sprite.setPosition(sf::Vector2f(-m_size.x, -m_size.y));
}

sf::Vector2f Earth::GetSize() { return m_size; }
bool Earth::FinishedMoving() { return m_finishMove; }
sf::Vector2f Earth::GetPosition() { return m_sprite.getPosition(); }
bool Earth::WaveHasStarted() { return m_initWave; }
void Earth::SetWaveHasStarted(bool value) { m_initWave = value; }