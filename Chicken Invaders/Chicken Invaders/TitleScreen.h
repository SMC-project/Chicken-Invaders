#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include "ResourceLoader.h"

using namespace sf;

class TitleScreen
{
public:
	Sprite leaderboard_button, leaderboard_hover, exit_button, exit_hover, side_texture;
	Sprite main_background, play_button,tip;
	void IntroMain_SetTextures(int WINDOW_WIDTH, int WINDOW_HEIGHT, ResourceLoader& resourceLoader);
	void IntroMain_Display(RenderWindow& map,TitleScreen& object);
	void menu_Select(RenderWindow& map, TitleScreen& object,bool& selected);
};

