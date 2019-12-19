#include "Leaderboard.h"

void Leaderboard::Init(const sf::Texture& texture, const sf::Font& font, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	m_sprite.setTexture(texture);
	m_sprite.setScale((float)WINDOW_WIDTH / texture.getSize().x, (float)WINDOW_HEIGHT / texture.getSize().y);

	m_inputPlayerName.setFont(font);
	m_inputPlayerName.setPosition(300, 530);
	for (int index = 0; index < 10; index++)
	{
		m_playerNames[index].setFont(font);
		m_playerNames[index].setPosition(1090, 300 + index * 57);
		m_playerScores[index].setFont(font);
		m_playerScores[index].setPosition(1380, 300 + index * 57);
	}
}

void Leaderboard::Draw(sf::RenderWindow& gameWindow)
{
	gameWindow.draw(m_sprite);
	gameWindow.draw(m_inputPlayerName);
	for (int index = 0; index < 10; index++)
	{
		if (m_playerNames[index].getString() == "")
			break;
		gameWindow.draw(m_playerNames[index]);
		gameWindow.draw(m_playerScores[index]);
	}
}

void Leaderboard::SetInputPlayerName(std::string newName)
{
	m_inputPlayerName.setString(newName);
}

void Leaderboard::SetPlayerData(int index, std::string name, long score)
{
	m_playerNames[index].setString(name);
	m_playerScores[index].setString(std::to_string(score));
}
