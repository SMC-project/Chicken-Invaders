#include "Present.h"


void Present::dropPresent()
{
	framePresent += animSpeed_Present;
	if (framePresent > frameCountPresent) framePresent = 0;
	setDropPresent.setTextureRect(IntRect(int(framePresent) * 256, 0, 256, 256));
}

void Present::setSpritePresent(Texture& present, Present& dropPresent)
{
	present.loadFromFile("Sprites/Extras/gift.png");
	dropPresent.setDropPresent.setTexture(present);
	dropPresent.setDropPresent.setScale(.15, .15);
}

void Present::drawPresent(RenderWindow& map, Present& dropPresent)
{
	dropPresent.dropPresent();
	map.draw(dropPresent.setDropPresent);
}

void Present::setPositionPresent(Present& newObject, float posX, float posY)
{
	newObject.setDropPresent.setPosition(posX, posY);
}
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

