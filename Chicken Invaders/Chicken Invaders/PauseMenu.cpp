#include "PauseMenu.h"

void PauseMenu::PauseMenu_SetTextures(int WINDOW_WIDTH, int WINDOW_HEIGHT, ResourceLoader& resourceLoader)
{
	pause_menu.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::PauseMenu_panel));
	pause_selection.setTexture(resourceLoader.GetTexture(ResourceLoader::TextureType::PauseMenu_select));
	pause_menu.setScale(1,1);
	pause_menu.setPosition(0, 0);
}

void PauseMenu::PauseMenu_Display(RenderWindow& map, PauseMenu& object)
{
	map.draw(object.pause_menu);
	map.draw(object.pause_selection);
	
}

void PauseMenu::PauseMenu_Select(RenderWindow& map, PauseMenu& object, int& selected)
{
	if (selected == 0)
	{
		
	}
	else if(selected == 1)
	{

	}
	else
	{

	}
}
