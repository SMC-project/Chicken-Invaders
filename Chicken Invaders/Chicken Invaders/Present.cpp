#include "Present.h"

Present::Present(int coordX, int coordY) :mCoordX(coordX),mCoordY(coordY)
{
}

void Present::setSpritePresent(Texture& presentTexture, Present& chickenPresent)
{
	presentTexture.loadFromFile("Sprites/Extras/gift.png");
	chickenPresent.presentSprite.setTexture(presentTexture);
	chickenPresent.presentSprite.setScale(.15, .15);
}

void Present::spawnPresent()
{
	framePresent += animeSpeedPresent;
	if (framePresent > frameCountPresent)framePresent = 0;
	presentSprite.setTextureRect(IntRect(int(framePresent) * 256, 0, 256, 256));

}

void Present::movePresent(Present& chickenPresent)
{

	bool drop = true;
	float x = chickenPresent.presentSprite.getPosition().x;
	float y = chickenPresent.presentSprite.getPosition().y;


	while (drop)
	{
		if (y > 0)
		{
			x += 5;
		}
		else if (y < 0) {
			std::cout << "else" << std::endl;
			drop = !drop;

		}


		chickenPresent.spawnPresent();
		chickenPresent.setPosition(chickenPresent);
	}
}

void Present::drawPresent(RenderWindow& map, Present& chickenPresent)
{
	chickenPresent.spawnPresent();

	map.draw(chickenPresent.presentSprite);
}

void Present::setPosition(Present& chickenPresent)
{
	float x = chickenPresent.mCoordX;
	float y = chickenPresent.mCoordY;
	chickenPresent.presentSprite.setPosition(x, y);
}


