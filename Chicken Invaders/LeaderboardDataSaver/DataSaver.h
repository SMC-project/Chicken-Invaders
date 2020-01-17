#pragma once
#include <string>

#ifndef Data_Saver_Exports
#define API_DATA_SAVER __declspec(dllexport)
#else
#define API_DATA_SAVER __declspec(dllimport)
#endif 

class API_DATA_SAVER DataSaver
{
private:
	struct PlayerData
	{
		std::string name;
		uint32_t score;
	};

public:
	void SaveData(std::string playerName, long playerScore);
	void LoadData();

	std::string& GetPlayerName(int playerIndex);
	long GetPlayerScore(int playerIndex);

private:
	PlayerData playerData[10];
};

