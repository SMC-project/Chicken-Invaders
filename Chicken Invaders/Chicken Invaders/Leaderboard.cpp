#include "Leaderboard.h"

void Leaderboard::Init(const sf::Texture& texture, const sf::Font& font, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale((float)WINDOW_WIDTH / texture.getSize().x, (float)WINDOW_HEIGHT / texture.getSize().y);

	m_inputPlayerName.setFont(font);
	for (int index = 0; index < 10; index++)
	{
		m_playerNames[index].setFont(font);
		m_playerScores[index].setFont(font);
	}
}

void Leaderboard::Draw(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_sprite);
	gameWindow.draw(m_inputPlayerName);
	for (int index = 0; index < 10; index++)
	{
		gameWindow.draw(m_playerNames[index]);
		gameWindow.draw(m_playerScores[index]);
	}
}

void Leaderboard::SetInputPlayerName(std::string newName)
{
}

void Leaderboard::SetPlayerData(int index, std::string name, long score)
{
}
