#include "TitleScreen.h"

void TitleScreen::IntroMain_SetTextures(int WINDOW_WIDTH, int WINDOW_HEIGHT, ResourceLoader& resourceLoader)
{
	side_texture.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_side));
	side_texture.setScale(.24, .24);
	side_texture.setPosition(-20,-340);

	main_background.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_background));
	main_background.setScale(1, 1);

	play_button.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_button_play));
	play_button.setScale(.2, .2);
	play_button.setPosition(700,450);

	leaderboard_button.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_button_leaderboard));
	leaderboard_button.setScale(.15, .15);
	leaderboard_button.setPosition(75, 115);

	leaderboard_hover.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_button_leaderboardHover));
	leaderboard_hover.setScale(.15, .15);
	leaderboard_hover.setPosition(50, 100);

	exit_button.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_button_exit));
	exit_button.setScale(.15, .15);
	exit_button.setPosition(75, 215);

	exit_hover.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_button_exitHover));
	exit_hover.setScale(.15, .15);
	exit_hover.setPosition(50, 200);

	tip.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::UI_tip));
	tip.setScale(.2, .2);
	tip.setPosition(700, 1000);
}

void TitleScreen::IntroMain_Display(RenderWindow& map, TitleScreen& object)
{
	map.draw(object.main_background);
	map.draw(object.play_button);
	map.draw(object.side_texture);
	map.draw(object.leaderboard_button);
	map.draw(object.exit_button);
	map.draw(object.tip);
}

void TitleScreen::menu_Select(RenderWindow& map, TitleScreen& object, bool& selected)
{
	if (selected)
	{
		map.draw(object.leaderboard_hover);
	}
	else
		map.draw(object.exit_hover);
}
