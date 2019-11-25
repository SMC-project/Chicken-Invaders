#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
enum class Level { Level_0, Level_1, Level_2, Level_3, Level_4, Level_5, Level_6, Level_7 };

class Bullet
{
private:
	Level m_bulletLevel;// Aceasta variabila memoreaza cate gloante vor fi initializate de nava
	std::vector <std::tuple<int, int, bool>> m_bullets; // Salveaza pozitia navei si ce gloante o sa lanseze in funtie de level
	std::vector<sf::Sprite> m_bulletSprites; //Imaginea gloantelor
	const int m_bulletSpeed=-10; // Viteza de deplasare a gloantelor
	sf::Texture m_bulletTexture;

protected:
	//Functie ce se apeleaza in Present_Collected
	void LevelPower(Level currentLevel);
	//Desenezi Gloantele pe mapa
	void DrawBullet(sf::RenderWindow& gameWindow);
	//Functie care schimba pozitia gloantelor;
	void BulletsPosition_Update(const int speed);
public:
	//Constructorul primeste varful navei;
	Bullet(int shipCenterPosition_x, int shipCenterPosition_y);
	//Move constructor necesar pentru vectorul de gloante din scena
	Bullet(Bullet&& other) noexcept;
	//Apelezi in momentul in care nava se intersecteaza cu un Present_Collected pentru a afisa noi gloante;
	void Present_Collected();
	//Verificam daca gloantele mai sunt pe ecran
	bool CheckIfBulletIsOnTheScreen(const int screenHeight);
	//Nava a fost distrusa
	void ResetBulletLevel();
	//Initializezi gloante in functie de level
	void Shot(sf::RenderWindow& gameWindow);
	//Operator de egal necesar pentru move constructor
	Bullet& operator=(const Bullet& other);
	
};

