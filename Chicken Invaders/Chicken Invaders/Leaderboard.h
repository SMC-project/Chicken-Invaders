#pragma once
#include<SFML/Graphics.hpp>

class Leaderboard
{
public:
	void Init(const sf::Texture& texture, const sf::Font& font, int WINDOW_WIDTH, int WINDOW_HEIGHT);

	void Draw(sf::RenderWindow& gameWindow);

	void SetInputPlayerName(std::string newName);

	void SetPlayerData(int index, std::string name, long score);

private:
	sf::Sprite m_sprite;
	sf::Text m_inputPlayerName;
	sf::Text m_playerNames[10];
	sf::Text m_playerScores[10];
};

