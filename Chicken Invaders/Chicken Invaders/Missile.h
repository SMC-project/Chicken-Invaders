#pragma once
#include"SFML/Graphics.hpp"
class Missile
{
private:
	
	sf::Sprite m_missileSprite;
	float m_frame=0;
	int m_frameCount = 15;
	float m_animSpeed =0.6;
	int m_foodNeeded = 25;
protected:
	void MissileAnimation();
public:
	Missile(int shipCenterPosition_x, int shipCenterPosition_y, const sf::Texture &texture);
	void DrawMissile(sf::RenderWindow &GameWindow);
	void UpdatePosition();
	void DrawAvailableMissile_OnTheScreen(sf::RenderWindow& GameWindow,int ShipFood);
	Missile &operator=(const Missile& other);
	Missile(Missile&& other) noexcept;
};

