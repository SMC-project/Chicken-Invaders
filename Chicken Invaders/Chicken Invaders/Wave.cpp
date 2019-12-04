#include "Wave.h"

void Wave::Init_asteroids(std::vector<Asteroid>& asteroids, ResourceLoader resource)
{
	float random_number;
	for (int index = 0; index < 15; index++)
	{
		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_x = random_number;

		random_number = rand() % 900 + rand() % 100;
		random_number = -random_number;
		float current_y = random_number;

		asteroids.push_back(std::move(Asteroid(sf::Vector2f(current_x, current_y), resource.GetTexture(ResourceLoader::TextureType::Asteroid))));
	}
}
