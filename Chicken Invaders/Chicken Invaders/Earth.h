#pragma once
#include<SFML/Graphics.hpp>

class Earth
{
public:
	void Init(const sf::Texture& texture);
	void SetPosition(sf::Vector2f initialPos);

	void Move();
	void SetTarget(sf::Vector2f target);
	void Draw(sf::RenderWindow& window);
	void Reset();

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	bool FinishedMoving();
	bool WaveHasStarted();
	void SetWaveHasStarted(bool value);
private:
	sf::Sprite m_sprite;
	sf::Vector2f m_size;

	sf::Vector2f m_targetPos;
	sf::Vector2f m_velocity;
	float m_speed = 0.05f;
	bool m_finishMove = true;
	bool m_initWave = false;
};

