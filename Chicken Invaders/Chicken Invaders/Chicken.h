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
	int frameCountchicken = 44;
	float animeSpeedChicken = 1.5;
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
	void moveChicken(float posX, float posY);
	//Getters
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
};
 
