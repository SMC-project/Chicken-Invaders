#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include "ResourceLoader.h"

using namespace sf;
class PauseMenu
{

public:
	Sprite pause_menu, pause_selection;
	void PauseMenu_SetTextures(int WINDOW_WIDTH, int WINDOW_HEIGHT, ResourceLoader& resourceLoader);
	void PauseMenu_Display(RenderWindow& map, PauseMenu& object);
	void PauseMenu_Select(RenderWindow& map, PauseMenu& object, int& selected);
};

