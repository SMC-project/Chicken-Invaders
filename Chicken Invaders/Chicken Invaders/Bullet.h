#pragma once
#include<iostream>
#include<vector>
enum Level {Level_1, Level_2, Level_3, Level_4, Level_5, Level_6, Level_7};

class Bullet
{
private:
	Level m_bulletLevel;
	std::vector <std::pair<std::pair<int, int>, bool>> m_bullets;
	float m_bulletSpeed;
    

public:
	//Constructor
	Bullet(std::pair<int, int> shipPosition);
	//Functie ce se apeleaza in Present_Collected
	void LevelPower();
	//Apelezi in momentul in care nava se intersecteaza cu un Present_Collected pentru a afisa noi gloante;
	void Present_Collected();
	//Pozitia in care se afla gloantele la fiecare 0,1 secunde;
	void BulletsPosition_Update();

};

