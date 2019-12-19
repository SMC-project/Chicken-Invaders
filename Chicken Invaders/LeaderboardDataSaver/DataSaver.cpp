#include "DataSaver.h"
#include <fstream>

void DataSaver::SaveData(std::string playerName, long playerScore)
{
	int startReplaceIndex = 10;
	for (int index = 0; index < 10; index++)
	{
		if (playerData[index].score < playerScore)
		{
			startReplaceIndex = index;
			break;
		}
	}

	PlayerData retainer, replacer;
	replacer.name = playerName;
	replacer.score = playerScore;

	for (int index = startReplaceIndex; index < 10; index++)
	{
		retainer.name = playerData[index].name;
		retainer.score = playerData[index].score;

		playerData[index].name = replacer.name;
		playerData[index].score = replacer.score;

		replacer.name = retainer.name;
		replacer.score = retainer.score;
	}

	std::ofstream out("leaderboard.log");
	for (int index = 0; index < 10; index++)
	{
		if (playerData[index].name == "")
			break;
		out << playerData[index].name << "\n" << playerData[index].score<<"\n";
	}
	out.close();
}

void DataSaver::LoadData()
{
	std::ifstream in("leaderboard.log");
	std::string auxStr;
	long auxLong;
	for (int index = 0; index < 10; index++)
	{
		if (!in.eof())
		{
			std::getline(in, auxStr);
			if (in.eof())
			{
				playerData[index].name = "";
				playerData[index].score = 0;
			}
			else
			{
				in >> auxLong;
				playerData[index].name = auxStr;
				playerData[index].score = auxLong;

				std::getline(in, auxStr); // To get rid of newline symbol in file (when you read a number it doesn't read that symbol)
			}
		}
		else
		{
			playerData[index].name = "";
			playerData[index].score = 0;
		}
	}
	in.close();
}

std::string& DataSaver::GetPlayerName(int playerIndex)
{
	return playerData[playerIndex].name;
}

long DataSaver::GetPlayerScore(int playerIndex)
{
	return playerData[playerIndex].score;
}
