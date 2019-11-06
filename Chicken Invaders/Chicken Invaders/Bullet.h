#pragma once
#include<iostream>
#include<vector>

enum class Level {Level_0, Level_1, Level_2, Level_3, Level_4, Level_5, Level_6, Level_7 };

class Bullet
{
private:
	Level m_bulletLevel;
	std::vector <std::pair<std::pair<int, int>, bool>> m_bullets;
	float m_bulletSpeed = 100;

protected:
	//Functie ce se apeleaza in Present_Collected
	void LevelPower(Level currentLevel);

public:
	//Constructorul primeste varful navei;
	Bullet(std::pair<int, int> shipCenterPosition);
	//Apelezi in momentul in care nava se intersecteaza cu un Present_Collected pentru a afisa noi gloante;
	void Present_Collected();
	//Pozitia in care se afla gloantele la fiecare 0,1 secunde;
	void BulletsPosition_Update();
	//Nava a fost distrusa
	void ResetShipLevel();
};

