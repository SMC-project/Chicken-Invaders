#pragma once
#include <SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

class ResourceLoader
{
public:
	enum class TextureType
	{
		Background,
		Earth,
		Ship,
		Asteroid,
		AsteroidFlame,
		Chicken,
		Gift,
		Meat,
		Explosion,
		Bullet,
		Egg,
		Rocket,
		UI_heart,
		UI_rocket,
		UI_button_play,
		UI_button_exit,
		UI_button_exitHover,
		UI_button_leaderboard,
		UI_button_leaderboardHover,
		UI_side,
		UI_tip,
		UI_background
	};

public:
	bool Init();
	const sf::Texture& GetTexture(const TextureType& type);
	const sf::Font& GetFont();
	sf::Music& GetMusic();

private:
	sf::Music m_music_background;
	sf::Font m_textFont;

	sf::Texture m_background;
	sf::Texture m_earth;

	sf::Texture m_ship;
	sf::Texture m_asteroid;
	sf::Texture m_asteroidFlame;
	sf::Texture m_chicken;
	//static sf::Texture m_boss;

	sf::Texture m_gift;
	sf::Texture m_meat;

	sf::Texture m_explosion;

	sf::Texture m_bullet;
	sf::Texture m_egg;
	sf::Texture m_rocket;

	sf::Texture m_uiHeart;
	sf::Texture m_uiRocket;

	sf::Texture m_uiButton_play;
	sf::Texture m_uiButton_exit;
	sf::Texture m_uiButton_exitHover;
	sf::Texture m_uiButton_leaderboard;
	sf::Texture m_uiButton_leaderboardHover;
	sf::Texture m_uiSide;
	sf::Texture m_uiTip;

	sf::Texture m_ui_background;
};

