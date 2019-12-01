#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<time.h>
#include<vector>
using namespace sf;
class Asteroid
{
private:
	
	float frame_asteroid1 = 0;
	int framecount_asteroid1 = 29;
	float animSpeed_Asteroid1 = .2;
	Sprite m_sprite_asteroid;
	Vector2f m_asteroidSize;

public:
	Asteroid(sf::Vector2f initialPos, const sf::Texture& texture);
	//Move constructor; needed for inserting (temporary) asteroids into the asteroids vector
	Asteroid(Asteroid&& other) noexcept;
	void Asteroid_animation();
	Asteroid& operator=(const Asteroid& other);

	//functions of the asteroids
	void draw_asteroid(RenderWindow& map);
	void asteroid_setPosition(float x_POS, float y_POS);
	bool Falldown(int screenHeight);

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
};
