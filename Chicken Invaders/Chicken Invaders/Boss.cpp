#include "Boss.h"

void Boss::BossAnimation()
{
	m_frame += m_animSpeed;
	if (m_frame > m_frameCount)
		m_frame = 0;
	m_sprite.setTextureRect(sf::IntRect(int(m_frame) * 256, 0, 256, 256));
}

Boss::Boss(const sf::Texture& texture,const int &waveNumber, const float& posX, const float& posY)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_size = sf::Vector2f(texture.getSize().x * m_sprite.getScale().x, texture.getSize().y * m_sprite.getScale().y);
	m_sprite.setScale(2, 2);
	m_sprite.setPosition(posX,posY);
	m_life = waveNumber * 10;

}

void Boss::DrawBoss(sf::RenderWindow& GameWindow)
{
	BossAnimation();
	GameWindow.draw(m_sprite);
}

void Boss::UpdatePosition(const float& posX, const float& posY)
{
	m_sprite.move(posX, posY);
}

Boss& Boss::operator=(const Boss& other)
{
	m_sprite.setTexture(*other.m_sprite.getTexture());
	m_sprite.setScale(other.m_sprite.getScale());
	m_sprite.setPosition(other.m_sprite.getPosition());
	m_frame = other.m_frame;
	m_frameCount = other.m_frameCount;
	m_animSpeed = other.m_animSpeed;
	m_size = other.m_size;
	m_life = other.m_life;
    m_leftOrRight = other.m_leftOrRight;
	return *this;
}

Boss::Boss(Boss&& other) noexcept
{
	m_sprite.setTexture(*other.m_sprite.getTexture());
	m_sprite.setScale(other.m_sprite.getScale());
	m_sprite.setPosition(other.m_sprite.getPosition());
	m_frame = other.m_frame;
	m_frameCount = other.m_frameCount;
	m_animSpeed = other.m_animSpeed;
	m_size = other.m_size;
	m_life = other.m_life;
	m_leftOrRight = other.m_leftOrRight;
}

const sf::Sprite& Boss::GetSprite() { return m_sprite; }

const sf::Vector2f& Boss::GetPosition(){return m_sprite.getPosition();}

const int& Boss::GetLife(){	return m_life;}

void Boss::ByeByeBoss(){ m_life--;}

const int& Boss::GetScore(){return 150;}

bool Boss::IsMovingRight()
{
	return m_leftOrRight;
}

void Boss::ChangeMovementAIComp()
{
	m_leftOrRight = !m_leftOrRight;
}
