#include "TitleScreen.h"

void TitleScreen::IntroMain_SetTextures(Texture& t1, Texture& t2, Texture& t3, Texture& t4, Texture& t5, Texture& t6, Texture& t7, Texture& t8, TitleScreen& object,const int WINDOW_WIDTH,const int WINDOW_HEIGHT)
{
	
	t5.loadFromFile("Sprites/user_interface/side_texture.png");
	object.side_texture.setTexture(t5);
	object.side_texture.setScale(.24, .24);
	object.side_texture.setPosition(-20,-340);
	t6.loadFromFile("Sprites/user_interface/main_background.png");
	object.main_background.setTexture(t6);
	object.main_background.setScale(1, 1);
	t7.loadFromFile("Sprites/user_interface/play_button.png");
	object.play_button.setTexture(t7);
	object.play_button.setScale(.2, .2);
	object.play_button.setPosition(700,450);

	t1.loadFromFile("Sprites/user_interface/leaderboard_button.png");
	object.leaderboard_button.setTexture(t1);
	object.leaderboard_button.setScale(.15, .15);
	object.leaderboard_button.setPosition(75, 115);
	t2.loadFromFile("Sprites/user_interface/leaderboard_hover.png");
	object.leaderboard_hover.setTexture(t2);
	object.leaderboard_hover.setScale(.15, .15);
	object.leaderboard_hover.setPosition(50, 100);
	t3.loadFromFile("Sprites/user_interface/exit_button.png");
	object.exit_button.setTexture(t3);
	object.exit_button.setScale(.15, .15);
	object.exit_button.setPosition(75, 215);
	t4.loadFromFile("Sprites/user_interface/exit_hover.png");
	object.exit_hover.setTexture(t4);
	object.exit_hover.setScale(.15, .15);
	object.exit_hover.setPosition(50, 200);
	t8.loadFromFile("Sprites/user_interface/tip.png");
	object.tip.setTexture(t8);
	object.tip.setScale(.2, .2);
	object.tip.setPosition(700, 1000);
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
