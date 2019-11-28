#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;

class TitleScreen
{
public:
	Sprite leaderboard_button, leaderboard_hover, exit_button, exit_hover, side_texture;
	Sprite main_background, play_button,tip;
	void IntroMain_SetTextures(Texture& t1, Texture& t2, Texture& t3, Texture& t4, Texture& t5,Texture& t6,Texture& t7, Texture& t8,TitleScreen& object, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
	void IntroMain_Display(RenderWindow& map,TitleScreen& object);
	void menu_Select(RenderWindow& map, TitleScreen& object,bool& selected);
};

