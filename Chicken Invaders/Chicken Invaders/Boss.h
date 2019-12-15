#pragma once
#include"SFML/Graphics.hpp"
class Boss
{

private:
	float m_frame = 0;
	int m_frameCount = 45;
	float m_animSpeed = 1.2;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
	int m_life;
	bool m_leftOrRight = false;

protected:
	void BossAnimation();

public:
	Boss(const sf::Texture &texture,const int &waveNumber, const float& posX, const float& posY);
	void DrawBoss(sf::RenderWindow& GameWindow);
	void UpdatePosition(const float& posX, const float &posY);
	Boss& operator=(const Boss& other);
	Boss(Boss&& other) noexcept;
	const sf::Sprite& GetSprite();
	const sf::Vector2f& GetPosition();
	const int& GetLife();
	void ByeByeBoss();
	const int& GetScore();
};

