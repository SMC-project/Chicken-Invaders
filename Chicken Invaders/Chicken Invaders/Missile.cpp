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

void Missile::DrawAvailableMissile_OnTheScreen(sf::RenderWindow& GameWindow, int ShipFood)
{
	sf::Sprite RocketCanv;
	sf::Texture RocketTextCanv;
	RocketTextCanv.loadFromFile("Sprites/Extras/RocketCanvas.png");
	RocketCanv.setTexture(RocketTextCanv);
	RocketCanv.setScale(1, 1);
	RocketCanv.setPosition(-10, 1030);
	int Nr = ShipFood / m_foodNeeded;
	for (int i = 0; i < Nr; i++)
	{
		RocketCanv.move(20, 0);
		GameWindow.draw(RocketCanv);
	}
}

Missile& Missile::operator=(const Missile& other)
{
	m_missileSprite = other.m_missileSprite;
	m_missileSprite.setScale(other.m_missileSprite.getScale());
	m_missileSprite.setPosition(other.m_missileSprite.getPosition());
	m_missileSprite.setRotation(other.m_missileSprite.getRotation());
	m_frame = other.m_frame;
	m_frameCount = other.m_frameCount;
	m_animSpeed = other.m_animSpeed;
	m_foodNeeded = other.m_foodNeeded;
	return *this;
}

Missile::Missile(Missile&& other) noexcept
{
	m_missileSprite = other.m_missileSprite;
	m_missileSprite.setScale(other.m_missileSprite.getScale());
	m_missileSprite.setPosition(other.m_missileSprite.getPosition());
	m_missileSprite.setRotation(other.m_missileSprite.getRotation());
	m_frame = other.m_frame;
	m_frameCount = other.m_frameCount;
	m_animSpeed = other.m_animSpeed;
	m_foodNeeded = other.m_foodNeeded;
	
}
