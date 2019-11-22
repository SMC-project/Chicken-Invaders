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
