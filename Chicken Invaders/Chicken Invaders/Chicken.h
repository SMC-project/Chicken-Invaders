#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<time.h>
#include<vector>

using namespace sf;
class Chicken
{
public:
	//Used for wave 4 and 5 variables
	int m_chickenIndex = 0;
	int m_moveDirectionFact = 1;
	int m_xOffsetFact = 0;
	int m_yOffsetFact = 0;
private:
	//These variables are used for moving between rows on the sprite sheet; in the constructor they are assigned the default value
	//And their values can be changed in a setter
	int m_startFrameLine;
	int m_endFrameLine;

	int m_frameLine = 0;
	float m_frameCol = 0;

	int m_frameCount = 45;
	float m_animSpeed = 1;

	float m_scoreChicken = 25;
	int m_life;

	Sprite m_chickenSprite;
	Vector2f m_chickenSize;

public:
	Chicken(Vector2f initialPos, const Texture& texture, const int& waveNumber);
	//Move constructor needed for inserting chickens in chicken vector 
	Chicken(Chicken&& other) noexcept;
	void chickenAnimation();
	Chicken& operator=(const Chicken& other);
	//Functions of chicken
	void drawChicken(RenderWindow& map);
	void setPositionChicken(float posX, float posY);
	void moveChicken(float posX, float posY);
	float getChickenScore();
	//Getters
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	const sf::Sprite& GetSprite();

	void SetAnimationFrames(int startLine, int endLine);
	const int& GetLife();
	void GetHit();
	bool IsOnTheScreen();
};
 
