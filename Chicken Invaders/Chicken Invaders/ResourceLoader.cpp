#include "ResourceLoader.h"
#include <thread>

bool ResourceLoader::Init1()
{
	if (m_textFont.loadFromFile("Fonts/Beaufort W01 Regular.ttf") == false)
	{
		printf("Error: couldn't load font.\n");
		return false;
	}

	return true;
}

bool ResourceLoader::Init2()
{
	bool perfectLoad = true;

	std::thread musicThread([this, &perfectLoad]() {
		if (m_music_background.openFromFile("Music/c.ogg") == false)
		{
			printf("Error: couldn't load music.\n");
			perfectLoad = false;
		}
		});

	std::thread backgroundThread([this, &perfectLoad]() {
		if (m_background.loadFromFile("Sprites/Extras/gbackground.png") == false)
		{
			printf("Error: couldn't load background.\n");
			perfectLoad = false;
		}
		});

	std::thread earthThread([this, &perfectLoad]() {
		if (m_earth.loadFromFile("Sprites/Extras/earth.png") == false)
		{
			printf("Error: couldn't load earth image.\n");
			perfectLoad = false;
		}
		});

	std::thread shipThread([this, &perfectLoad]() {
		if (m_ship.loadFromFile("Sprites/ship.png") == false)
		{
			printf("Error: couldn't load ship.\n");
			perfectLoad = false;
		}
		});

	std::thread asteroidFlameThread([this, &perfectLoad]() {
		if (m_asteroidFlame.loadFromFile("Sprites/Enemy/asteroidFlame.png") == false)
		{
			printf("Error: couldn't load flame asteroid.\n");
			perfectLoad = false;
		}
		});

	std::thread asteroidThread([this, &perfectLoad]() {
		if (m_asteroid.loadFromFile("Sprites/Enemy/asteroidNormal.png") == false)
		{
			printf("Error: couldn't load normal asteroid.\n");
			perfectLoad = false;
		}
		});

	std::thread chickenThread([this, &perfectLoad]() {
		if (m_chicken.loadFromFile("Sprites/Enemy/chicken.png") == false)
		{
			printf("Error: couldn't load chicken.\n");
			perfectLoad = false;
		}
		});

	std::thread bossThread([this, &perfectLoad]() {
		if (m_boss.loadFromFile("Sprites/Enemy/boss.png") == false)
		{
			printf("Error: couldn't load boss.\n");
			perfectLoad = false;
		}
		});

	std::thread giftThread([this, &perfectLoad]() {
		if (m_gift.loadFromFile("Sprites/Extras/gift.png") == false)
		{
			printf("Error: couldn't load gift.\n");
			perfectLoad = false;
		}
		});

	std::thread meatThread([this, &perfectLoad]() {
		if (m_meat.loadFromFile("Sprites/Extras/meat.png") == false)
		{
			printf("Error: couldn't load meat.\n");
			perfectLoad = false;
		}
		});

	std::thread explosionThread([this, &perfectLoad]() {
		if (m_explosion.loadFromFile("Sprites/Extras/explosion.png") == false)
		{
			printf("Error: couldn't load explosion.\n");
			perfectLoad = false;
		}
		});

	std::thread bulletThread([this, &perfectLoad]() {
		if (m_bullet.loadFromFile("Sprites/Weapons/bullet.png") == false)
		{
			printf("Error: couldn't load bullet.\n");
			perfectLoad = false;
		}
		});

	std::thread eggThread([this, &perfectLoad]() {
		if (m_egg.loadFromFile("Sprites/Weapons/egg.png") == false)
		{
			printf("Error: couldn't load egg.\n");
			perfectLoad = false;
		}
		});

	std::thread rocketThread([this, &perfectLoad]() {
		if (m_rocket.loadFromFile("Sprites/Weapons/rocket.png") == false)
		{
			printf("Error: couldn't load rocket.\n");
			perfectLoad = false;
		}
		});

	std::thread heartThread([this, &perfectLoad]() {
		if (m_uiHeart.loadFromFile("Sprites/Extras/heart.png") == false)
		{
			printf("Error: couldn't load heart.\n");
			perfectLoad = false;
		}
		});

	std::thread rocketUIThread([this, &perfectLoad]() {
		if (m_uiRocket.loadFromFile("Sprites/Weapons/rocketUI.png") == false)
		{
			printf("Error: couldn't load ui rocket.\n");
			perfectLoad = false;
		}
		});

	std::thread playButtonThread([this, &perfectLoad]() {
		if (m_uiButton_play.loadFromFile("Sprites/user_interface/play_button.png") == false)
		{
			printf("Error: couldn't load play button.\n");
			perfectLoad = false;
		}
		});

	std::thread exitButtonThread([this, &perfectLoad]() {
		if (m_uiButton_exit.loadFromFile("Sprites/user_interface/exit_button.png") == false)
		{
			printf("Error: couldn't load exit button.\n");
			perfectLoad = false;
		}
		});

	std::thread exitHoverThread([this, &perfectLoad]() {
		if (m_uiButton_exitHover.loadFromFile("Sprites/user_interface/exit_hover.png") == false)
		{
			printf("Error: couldn't load exit hover button.\n");
			perfectLoad = false;
		}
		});

	std::thread leaderboardButtonThread([this, &perfectLoad]() {
		if (m_uiButton_leaderboard.loadFromFile("Sprites/user_interface/leaderboard_button.png") == false)
		{
			printf("Error: couldn't load leaderboard button.\n");
			perfectLoad = false;
		}
		});

	std::thread leaderboardHoverButtonThread([this, &perfectLoad]() {
		if (m_uiButton_leaderboardHover.loadFromFile("Sprites/user_interface/leaderboard_hover.png") == false)
		{
			printf("Error: couldn't load leaderboard hover button.\n");
			perfectLoad = false;
		}
		});

	std::thread sideTextureThread([this, &perfectLoad]() {
		if (m_uiSide.loadFromFile("Sprites/user_interface/side_texture.png") == false)
		{
			printf("Error: couldn't load side texture.\n");
			perfectLoad = false;
		}
		});

	std::thread tipThread([this, &perfectLoad]() {
		if (m_uiTip.loadFromFile("Sprites/user_interface/tip.png") == false)
		{
			printf("Error: couldn't load tip.\n");
			perfectLoad = false;
		}
		});

	std::thread mainMenuBackgroundThread([this, &perfectLoad]() {
		if (m_ui_background.loadFromFile("Sprites/user_interface/main_background.png") == false)
		{
			printf("Error: couldn't load title screen's background.\n");
			perfectLoad = false;
		}
		});

	std::thread PauseMenuPanelThread([this, &perfectLoad]() {
		if (m_p_panel.loadFromFile("Sprites/user_interface/pause_panel.png") == false)
		{
			printf("Error: couldn't load pause menu's panel.\n");
			perfectLoad = false;
		}
		});

	std::thread PauseMenuSelectThread([this, &perfectLoad]() {
		if (m_p_select.loadFromFile("Sprites/user_interface/pause_select.png") == false)
		{
			printf("Error: couldn't load pause menu's panel.\n");
			perfectLoad = false;
		}
		});

	std::thread leaderboardThread([this, &perfectLoad]() {
		if (m_leaderboard.loadFromFile("Sprites/user_interface/leaderboard_panel.jpg") == false)
		{
			printf("Error: couldn't load leaderboardl.\n");
			perfectLoad = false;
		}
		});

	
	musicThread.join();
	backgroundThread.join();
	earthThread.join();
	shipThread.join();
	asteroidFlameThread.join();
	asteroidThread.join();
	chickenThread.join();
	bossThread.join();
	giftThread.join();
	meatThread.join();
	explosionThread.join();
	bulletThread.join();
	eggThread.join();
	rocketThread.join();
	heartThread.join();
	rocketUIThread.join();
	PauseMenuPanelThread.join();
	PauseMenuSelectThread.join();
	playButtonThread.join();
	exitButtonThread.join();
	exitHoverThread.join();
	leaderboardButtonThread.join();
	leaderboardHoverButtonThread.join();
	sideTextureThread.join();
	tipThread.join();
	mainMenuBackgroundThread.join();
	leaderboardThread.join();

	return perfectLoad;
}

const sf::Texture& ResourceLoader::GetTexture(const TextureType& type)
{
	switch (type)
	{
	case TextureType::Background:
		return m_background;
	case TextureType::Earth:
		return m_earth;
	case TextureType::Ship:
		return m_ship;
	case TextureType::Asteroid:
		return m_asteroid;
	case TextureType::AsteroidFlame:
		return m_asteroidFlame;
	case TextureType::Chicken:
		return m_chicken;
	case TextureType::Boss:
		return m_boss;
	case TextureType::Gift:
		return m_gift;
	case TextureType::Meat:
		return m_meat;
	case TextureType::Explosion:
		return m_explosion;
	case TextureType::Bullet:
		return m_bullet;
	case TextureType::Egg:
		return m_egg;
	case TextureType::Rocket:
		return m_rocket;
	case TextureType::UI_heart:
		return m_uiHeart;
	case TextureType::UI_rocket:
		return m_uiRocket;
	case TextureType::UI_button_play:
		return m_uiButton_play;
	case TextureType::UI_button_exit:
		return m_uiButton_exit;
	case TextureType::UI_button_exitHover:
		return m_uiButton_exitHover;
	case TextureType::UI_button_leaderboard:
		return m_uiButton_leaderboard;
	case TextureType::UI_button_leaderboardHover:
		return m_uiButton_leaderboardHover;
	case TextureType::UI_side:
		return m_uiSide;
	case TextureType::UI_tip:
		return m_uiTip;
	case TextureType::UI_background:
		return m_ui_background;
	case TextureType::PauseMenu_panel:
		return m_p_panel;
	case TextureType::PauseMenu_select:
		return m_p_select;
	case TextureType::Leaderboard:
		return m_leaderboard;
	}
}

const sf::Font& ResourceLoader::GetFont()
{
	return m_textFont;
}

sf::Music& ResourceLoader::GetMusic()
{
	return m_music_background;
}

