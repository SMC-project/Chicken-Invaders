#include "Wave.h"

void Wave::fisrtWavePosition(Chicken chicken[5][8])
{

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
			chicken[i][j].sprite_chicken.setPosition(400 + j*200 - j*50, 50 + i*200 - i*100);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
			chicken[i][j].Animation();
}

void Wave::drawWave(RenderWindow& map,Chicken chicken[5][8])
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
			map.draw(chicken[i][j].sprite_chicken);
}

void Wave::setSprite(Texture& enemy,Chicken chicken[5][8])
{
	enemy.loadFromFile("Sprites/Enemy/Normal Chicken/Idle/chicken_animation.png");
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 8; j++)
		{
			chicken[i][j].sprite_chicken.setTexture(enemy);
			chicken[i][j].sprite_chicken.setScale(.3, .3);
		}
}
