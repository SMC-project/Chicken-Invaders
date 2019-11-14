#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>

#include "Player.h"


void GameLoop(sf::RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);

int main()
{
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	sf::RenderWindow gameWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chicken Invaders DX", sf::Style::Fullscreen);
	gameWindow.setFramerateLimit(30);

	GameLoop(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

	return 0;
}


void GameLoop(sf::RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
	sf::Texture texture_background;
	texture_background.loadFromFile("Sprites/Extras/background.png");
	sf::Sprite sprite_background(texture_background);
	sprite_background.setPosition(0, 0);
	sprite_background.setScale(1, 1);
	
	Player player("Sprites/Ship/ship.png", std::make_pair(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));

	while (gameWindow.isOpen())
	{
		sf::Event eventHandler;
		while (gameWindow.pollEvent(eventHandler))
		{
			if (eventHandler.type == sf::Event::KeyPressed)
			{
				if (eventHandler.key.code == sf::Keyboard::Left)
					player.SetMoveDirection(-1);
				if (eventHandler.key.code == sf::Keyboard::Right)
					player.SetMoveDirection(1);
			}
			if (eventHandler.type == sf::Event::KeyReleased)
			{
				if (eventHandler.key.code == sf::Keyboard::Escape)
					gameWindow.close();
				if (eventHandler.key.code == sf::Keyboard::Left || eventHandler.key.code == sf::Keyboard::Right)
					player.SetMoveDirection(0);

			}
		}

		//All object's movement
		player.MoveShip(WINDOW_WIDTH);

		gameWindow.clear();

		//Here is where we draw stuff;
		gameWindow.draw(sprite_background);
		player.DrawShip(gameWindow);

		gameWindow.display();

	}
}


