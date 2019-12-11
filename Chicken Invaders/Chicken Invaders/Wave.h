#pragma once
#include"Chicken.h"
#include "Asteroid.h"
#include"Explosion.h"
#include "Present.h"
#include<time.h>
#include "ResourceLoader.h"

class Wave
{
private:
	//used in the first wave changing the state of direction
	bool left_or_right_movement = true;
	//used to get random initial position
	int random_number;

	//Wave 5 variables
	const float pi = 3.14159265359;
	int wave4and5NrChickens = 20;
	float radius1 = 600;
	float radius2 = 250;
	float degrees = 0;
	
public:
	bool m_leftOrRightMovement = true;
	bool m_wave7_left_right[30] = {1};
	bool m_wave7_left_right2[30] = { 1 };
	std::vector<Chicken> chickens;
	ResourceLoader resurceLoader;

	void Wave1Init(std::vector<Chicken>& chickens, const Texture& texture, int WINDOW_WIDTH, int WINDOW_HEIGHT);
	void Wave1SetPosition(std::vector<Chicken>& chickens, int Window_width, int Window_height);
	void Wave1Movement(std::vector<Chicken>& chickens);

	void Wave3Init(const Texture& texture, std::vector<Asteroid>& asteroids);

	void Wave4And5Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void Wave4And5Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	void wave6Init(std::vector<Asteroid>& asteroids, const Texture& texture, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void wave6Movement(std::vector<Asteroid>& asteroids, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	void Wave7Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void Wave7Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	void Wave8Init(std::vector<Chicken>& chickens, ResourceLoader& resourceLoader, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void Wave8Movement(std::vector<Chicken>& chickens, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	void Wave9Init(std::vector<Asteroid>& asteroids, const Texture& texture, int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void Wave9Movement(std::vector<Asteroid>& asteroids, int SCRENN_WIDTH, int SCREEN_HEIGHT);
};

