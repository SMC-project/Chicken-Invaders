#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<time.h>
#include<vector>

using namespace sf;
class Chicken
{
private:
	float frameChicken = 0;
	int frameCountchicken = 45;
	float animeSpeedChicken = 0.03;
	Sprite m_chickenSprite;
	Vector2f m_chickenSize;

public:
	Chicken(Vector2f initialPos, const Texture& texture);
	//Move constructor needed for inserting chickens in chicken vector 
	Chicken(Chicken&& other) noexcept;
	void chickenAnimation();
	Chicken& operator=(const Chicken& other);
	//Functions of chicken
	void drawChicken(RenderWindow& map);
	void setPositionChicken(float posX, float posY);
	void chickenMovement(int screenWidth);
	//Getters
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
};
 
