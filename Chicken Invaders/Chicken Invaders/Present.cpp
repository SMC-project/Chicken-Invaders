#include "Present.h"


void Present::dropPresent()
{
	framePresent += animSpeed_Present;
	if (framePresent > frameCountPresent) framePresent = 0;
	setDropPresent.setTextureRect(IntRect(int(framePresent) * 256, 0, 256, 256));
}

void Present::setSpritePresent(const Texture& texture)
{
	setDropPresent.setTexture(texture);
	setDropPresent.setScale(.15, .15);
}

void Present::drawPresent(RenderWindow& map)
{
	dropPresent();
	map.draw(setDropPresent);
}

void Present::setPositionPresent(float posX, float posY)
{
	setDropPresent.setPosition(posX, posY);
}

bool Present::fallDownPresent(int windowHeight)
{
	setDropPresent.move(0, fallDownSpeed);
	if (setDropPresent.getPosition().y > windowHeight)
		return true;
	return false;
}

