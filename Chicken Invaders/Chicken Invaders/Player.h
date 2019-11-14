#pragma once
#include<SFML/Graphics.hpp>

class Player
{
public:
	//Load the sprite of the player, set and retain it's initial pos in the center of the screen, calculate pixelSize
	Player(const std::string& spritePath, sf::Vector2<int> initialPos);

	//Draw the sprite to the window, it may be more complex in the future (with animations) so I made it a method.
	void DrawShip(sf::RenderWindow& gameWindow);
	//Move the ship, the parameter is used for boundry check so that it doesn't go off-screen
	void MoveShip(int WINDOW_WIDTH);
	//Move right is used to know which value to set in the movement vector and the factor for how much to move (max value of 1)
	//For a more detalied explanation check 'm_movement' description
	void SetMovement(bool moveRight, float factor);

	//Load the sprites into a vector of sprites and set their positions
	void LoadLiveSprites(const std::string& livesSpritePath);
	//Draw how many lives we have left on the screen
	void DrawLives(sf::RenderWindow& gameWindow);

	//Check if we collided with something; to do this we check the upper left corner and lower right corner of the sprites
	//Returns true if we collided with something
	bool CheckCollision(sf::Vector2<float> upperLeft, sf::Vector2<int> lowerRight);
	//Decrement lives and reset position; in the future it will have a GameOver functionality
	void Die();

private:
	sf::Vector2<float> m_initialPos;	//We store the initial position in order to reset the player when he dies
	sf::Vector2<int> m_shipSize;		//Retain the pixels covered by the sprite; used for collision check
	sf::Sprite m_spriteShip;			//The sprite of the ship
	sf::Texture m_textureShip;			//The texture that is used to render the sprite

	float m_speed = 20;					//Speed used for ship movement
	float m_boundryOffset = 50;			//Used to have some space between the border of the screen and the ship when moving

	/* Movement is a bit more complex:
	*		-on the 'x' component it will retain negative values meaning that we pressed left arrow
	*		-on the 'y' component it will retain positive values meaning that we pressed right arrow
	*		-when we release a key the position corresponding to the key will be set to 0 meaning that we shouldn't move
	*	The reason why this is not a float is because when we press two keys at the same time, when we release one there will be an 
	* interruption in movement because we would set the float to 0, and then you need to relase the key and press it again to move.
	*	By implementing it as a vector, when we release a key it will set only one position in the vector to 0, not influencing the other
	* making movement smooth without interruptions
	*/
	sf::Vector2<float> m_movement;

	int m_lives = 3;				//Number a lives the player has; it is decremented when he dies
	sf::Sprite m_spriteLives[3];	//Sprites for the UI lives components
	sf::Texture m_textureLives[3];	//Texture for the lives sprites
};

