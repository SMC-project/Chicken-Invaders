#pragma once
#include"SFML/Graphics.hpp"
class Missile
{
private:

	sf::Sprite m_missileSprite;
	float m_frame = 0;
	int m_frameCount = 15;
	float m_animSpeed = 0.6;
	int m_foodNeeded = 25;
	int m_missilePosition_X;
	int m_missilePosition_Y;


protected:
	void MissileAnimation();
public:
	Missile(int shipCenterPosition_x, int shipCenterPosition_y, const sf::Texture& texture);
	void DrawMissile(sf::RenderWindow& GameWindow);
	void UpdatePosition(int shipCenterPosition_x);
	Missile& operator=(const Missile& other);
	Missile(Missile&& other) noexcept;
	bool ItIsTimeForExplosion();
	sf::Vector2f GetPosition();
};

