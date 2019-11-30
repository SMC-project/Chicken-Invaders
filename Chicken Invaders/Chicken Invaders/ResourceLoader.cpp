#include "ResourceLoader.h"

bool ResourceLoader::Init1()
{
	if (m_textFont.loadFromFile("Fonts/Montserrat-Regular.ttf") == false)
	{
		printf("Error: couldn't load font.\n");
		return false;
	}

	return true;
}

bool ResourceLoader::Init2()
{
	if (m_music_background.openFromFile("Music/c.ogg") == false)
	{
		printf("Error: couldn't load music.\n");
		return false;
	}

	if (m_background.loadFromFile("Sprites/Extras/gbackground.png") == false)
	{
		printf("Error: couldn't load background.\n");
		return false;
	}
	if (m_earth.loadFromFile("Sprites/Extras/earth.png") == false)
	{
		printf("Error: couldn't load earth image.\n");
		return false;
	}

	if (m_ship.loadFromFile("Sprites/ship.png") == false)
	{
		printf("Error: couldn't load ship.\n");
		return false;
	}
	if (m_asteroidFlame.loadFromFile("Sprites/Enemy/asteroidFlame.png") == false)
	{
		printf("Error: couldn't load flame asteroid.\n");
		return false;
	}
	if (m_asteroid.loadFromFile("Sprites/Enemy/asteroidNormal.png") == false)
	{
		printf("Error: couldn't load normal asteroid.\n");
		return false;
	}
	if (m_chicken.loadFromFile("Sprites/Enemy/chicken.png") == false)
	{
		printf("Error: couldn't load chicken.\n");
		return false;
	}
	//m_boss;

	if (m_gift.loadFromFile("Sprites/Extras/gift.png") == false)
	{
		printf("Error: couldn't load gift.\n");
		return false;
	}
	if (m_meat.loadFromFile("Sprites/Extras/meat.png") == false)
	{
		printf("Error: couldn't load meat.\n");
		return false;
	}

	if (m_explosion.loadFromFile("Sprites/Extras/explosion.png") == false)
	{
		printf("Error: couldn't load explosion.\n");
		return false;
	}

	if (m_bullet.loadFromFile("Sprites/Weapons/bullet.png") == false)
	{
		printf("Error: couldn't load bullet.\n");
		return false;
	}
	if (m_egg.loadFromFile("Sprites/Weapons/egg.png") == false)
	{
		printf("Error: couldn't load egg.\n");
		return false;
	}
	if (m_rocket.loadFromFile("Sprites/Weapons/rocket.png") == false)
	{
		printf("Error: couldn't load rocket.\n");
		return false;
	}

	if (m_uiHeart.loadFromFile("Sprites/Extras/heart.png") == false)
	{
		printf("Error: couldn't load heart.\n");
		return false;
	}
	if (m_uiRocket.loadFromFile("Sprites/Weapons/rocketUI.png") == false)
	{
		printf("Error: couldn't load ui rocket.\n");
		return false;
	}

	if (m_uiButton_play.loadFromFile("Sprites/user_interface/play_button.png") == false)
	{
		printf("Error: couldn't load play button.\n");
		return false;
	}
	if (m_uiButton_exit.loadFromFile("Sprites/user_interface/exit_button.png") == false)
	{
		printf("Error: couldn't load exit button.\n");
		return false;
	}
	if (m_uiButton_exitHover.loadFromFile("Sprites/user_interface/exit_hover.png") == false)
	{
		printf("Error: couldn't load exit hover button.\n");
		return false;
	}
	if (m_uiButton_leaderboard.loadFromFile("Sprites/user_interface/leaderboard_button.png") == false)
	{
		printf("Error: couldn't load leaderboard button.\n");
		return false;
	}
	if (m_uiButton_leaderboardHover.loadFromFile("Sprites/user_interface/leaderboard_hover.png") == false)
	{
		printf("Error: couldn't load leaderboard hover button.\n");
		return false;
	}
	if (m_uiSide.loadFromFile("Sprites/user_interface/side_texture.png") == false)
	{
		printf("Error: couldn't load side texture.\n");
		return false;
	}
	if (m_uiTip.loadFromFile("Sprites/user_interface/tip.png") == false)
	{
		printf("Error: couldn't load tip.\n");
		return false;
	}

	if (m_ui_background.loadFromFile("Sprites/user_interface/main_background.png") == false)
	{
		printf("Error: couldn't load title screen's background.\n");
		return false;
	}

	return true;
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

