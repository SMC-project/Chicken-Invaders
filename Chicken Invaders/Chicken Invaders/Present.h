#pragma once
#include<SFML/Graphics.hpp>

#include<iostream>
#include<time.h>

using namespace sf;
class Present
{
private:
	Sprite m_sprite;
	float m_framePresent = 0;
	int m_frameCountPresent = 45;
	float m_animSpeed_Present = .8;
	float m_fallDownSpeed = 10;

public:
	Present(sf::Vector2f initialPos, const sf::Texture& texture);
	Present(Present&& other) noexcept;
	Present& operator=(const Present& other);
	void DropPresent();
	//functions of presents
	void SetSpritePresent(const Texture& texture);
	void DrawPresent(RenderWindow& map);
	void SetPositionPresent(float posX, float posY);
	bool FallDownPresent(int windowHeight);
	const sf::Sprite& GetSprite();
};
