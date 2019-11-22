#include "Present.h"

Present::Present(int coordX, int coordY) :mCoordX(coordX),mCoordY(coordY)
{
}

void Present::setSpritePresent(Texture& presentTexture, Present& chickenPresent)
{
	presentTexture.loadFromFile("Sprites/Extras/gift.png");
	chickenPresent.present.setTexture(presentTexture);
	chickenPresent.present.setScale(.15, .15);
}

void Present::dropPresent()
{
	framePresent += animeSpeedPresent;
	if (framePresent > frameCountPresent)framePresent = 0;
	present.setTextureRect(IntRect(int(framePresent) * 256, 0, 256, 256));

}

void Present::drawPresent(RenderWindow& map, Present& chickenPresent)
{
	chickenPresent.dropPresent();

	map.draw(chickenPresent.present);
}

void Present::setPosition(Present& chickenPresent, float x, float y)
{
	chickenPresent.present.setPosition(x, y);
}


