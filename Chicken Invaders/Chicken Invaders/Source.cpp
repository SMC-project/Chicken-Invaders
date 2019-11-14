#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>

#include "Player.h"
#include "Chicken.h"
using namespace sf;


void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);

int main()
{
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	RenderWindow gameWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chicken Invaders DX", Style::Fullscreen);
	gameWindow.setFramerateLimit(30);

	GameLoop(gameWindow, WINDOW_WIDTH, WINDOW_HEIGHT);

	return 0;
}


void GameLoop(RenderWindow& gameWindow, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
	Chicken chicken;
	Texture texture_background, c;
	texture_background.loadFromFile("Sprites/Extras/background.png");
	c.loadFromFile("Sprites/Enemy/Normal Chicken/Idle/chicken_animation.png");
	Sprite sprite_background(texture_background);
	sprite_background.setPosition(0, 0);
	sprite_background.setScale(1, 1);
	chicken.sprite_chicken.setTexture(c);
	chicken.sprite_chicken.setScale(.5, .5);
	
	Player player("Sprites/Ship/ship.png", std::make_pair(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 7 / 8));

	while (gameWindow.isOpen())
	{
		Event eventHandler;
		while (gameWindow.pollEvent(eventHandler))
		{
			if (eventHandler.type == Event::KeyPressed)
			{
				if (eventHandler.key.code == Keyboard::Left)
					player.SetMoveDirection(-1);
				if (eventHandler.key.code == Keyboard::Right)
					player.SetMoveDirection(1);
			}
			if (eventHandler.type == Event::KeyReleased)
			{
				if (eventHandler.key.code == Keyboard::Escape)
					gameWindow.close();
				if (eventHandler.key.code == Keyboard::Left || eventHandler.key.code == Keyboard::Right)
					player.SetMoveDirection(0);
			}
		}

		//All object's movement
		player.MoveShip(WINDOW_WIDTH);
		chicken.Animation();

		gameWindow.clear();

		//Here is where we draw stuff;
		gameWindow.draw(sprite_background);
		gameWindow.draw(chicken.sprite_chicken);
		player.DrawShip(gameWindow);

		gameWindow.display();
	}
}


