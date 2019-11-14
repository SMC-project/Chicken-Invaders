#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include "Chicken.h"
using namespace sf;

void GameLoop(sf::RenderWindow& gameWindow);

int main()
{
	sf::RenderWindow gameWindow(sf::VideoMode(1920, 1080), "gameWindow", sf::Style::Fullscreen);
	gameWindow.setFramerateLimit(30);

	GameLoop(gameWindow);

	return 0;
}


void GameLoop(sf::RenderWindow& gameWindow)
{
	Chicken chicken;
	sf::Texture texture_background, c;
	texture_background.loadFromFile("Sprites/Extras/background.png");
	c.loadFromFile("Sprites/Enemy/Normal Chicken/Idle/chicken_animation.png");
	sf::Sprite sprite_background(texture_background);
	sprite_background.setPosition(0, 0);
	sprite_background.setScale(1, 1);
	chicken.sprite_chicken.setTexture(c);
	chicken.sprite_chicken.setScale(.5, .5);
	
	

	while (gameWindow.isOpen())
	{
		sf::Event eventHandler;
		while (gameWindow.pollEvent(eventHandler))
		{
			if (eventHandler.type == sf::Event::KeyReleased)
			{
				if (eventHandler.key.code == sf::Keyboard::Escape)
					gameWindow.close();
			}

		}

		chicken.Animation();

		gameWindow.clear();

		//Here is where we draw stuff;
		gameWindow.draw(sprite_background);
		gameWindow.draw(chicken.sprite_chicken);
		gameWindow.display();

	}
}


