#include "Missile.h"

void Missile::MissileAnimation()
{
	m_frame += m_animSpeed;
	if (m_frame > m_frameCount)
		m_frame = 0;
	m_missileSprite.setTextureRect(sf::IntRect(int(m_frame) * 128, 0, 128, 256));
}

Missile::Missile(int shipCenterPosition_x, int shipCenterPosition_y, const sf::Texture &texture)
{
	m_missileSprite.setTexture(texture);
	m_missileSprite.setScale(0.28, 0.28);
	m_missileSprite.setPosition(shipCenterPosition_x + 44, shipCenterPosition_y - 10);
}

void Missile::DrawMissile(sf::RenderWindow& GameWindow)
{
	MissileAnimation();
	GameWindow.draw(m_missileSprite);
}
