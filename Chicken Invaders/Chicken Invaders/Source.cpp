#include <iostream>
#include<SFML/Graphics.hpp>
#include<Windows.h>


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
	sf::Texture texture_background;
	texture_background.loadFromFile("Sprites/Extras/background.png");
	sf::Sprite sprite_background(texture_background);
	sprite_background.setPosition(0, 0);
	sprite_background.setScale(1, 1);
	

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

		gameWindow.clear();

		//Here is where we draw stuff;
		gameWindow.draw(sprite_background);

		gameWindow.display();

	}
}


