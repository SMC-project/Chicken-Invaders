#pragma once
#include<SFML/Graphics.hpp>

class Player
{
public:
	//Load the sprite of the player, set and retain it's initial pos in the center of the screen, calculate pixelSize
	void Init(sf::Vector2f initialPos, const sf::Texture& texture, const sf::Texture& uiMissileTexture);

	//Draw the sprite to the window, it may be more complex in the future (with animations) so I made it a method.
	void DrawShip(sf::RenderWindow& gameWindow, float deltaTimeSeconds);
	//Move the ship, the parameter is used for boundry check so that it doesn't go off-screen
	void MoveShip(int WINDOW_WIDTH);
	//Move right is used to know which value to set in the movement vector and the factor for how much to move (max value of 1)
	//For a more detalied explanation check 'm_movement' description
	void SetMovement(bool moveRight, float factor);

	//Load the sprites into a vector of sprites and set their positions
	void LoadLiveSprites(const sf::Texture& texture);
	//Draw how many lives we have left on the screen
	void DrawLives(sf::RenderWindow& window);

	//Load the font for the text and set up the text's position, size, initial value.
	void SetUpScore(const sf::Font& font);
	//Add to the score, called when defeating an enemy
	void UpdateScore(int value);
	//Draw the score to the screen
	void DrawScore(sf::RenderWindow& window);

	//Decrement lives and reset position; in the future it will have a GameOver functionality
	void Die();
	bool IsImmortal();

	void Reset();

	//Will change the rect of the spritesheet to simulate an animation
	//It knows which rect to pick so that it renders the expected animation
	void Animate();

	void DrawUIMissile(sf::RenderWindow& GameWindow, const sf::Texture& texture);
	void AddMeat();

	bool IsDead();
	sf::Vector2f GetPosition();
	int GetNrMissiles();
	void ShootMissile();
	const sf::Sprite& GetSprite();
	uint32_t GetScore();
	const sf::Vector2f& GetSize();
	int GetLifes();

private:
	sf::Vector2f m_initialPos;	//We store the initial position in order to reset the player when he dies
	sf::Vector2f m_shipSize;		//Retain the pixels covered by the sprite; used for collision check
	sf::Sprite m_spriteShip;			//The sprite of the ship

	int m_meatNeededForRocket = 25;
	int m_currentMeat = 0;
	int m_nrMissiles = 0;

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
	sf::Vector2f m_movement;

	float m_currentImmortalTime = 0.0f;
	float m_maxImmortalTime = 2.5f;
	bool m_isImmortal = false;
	int m_lives = 3;				//Number a lives the player has; it is decremented when he dies
	sf::Sprite m_spriteLives[3];	//Sprites for the UI lives components

	//The line and column indexes of the sprite to render, the animation has 4 rows of 10 sprites each
	int m_animColFrame = 0;
	int m_animRowFrame = 0;

	//Score variables, I may put them the game manager later
	uint32_t m_score = 0;
	sf::Text m_scoreText;

	sf::Sprite m_ui_rocket;
};

