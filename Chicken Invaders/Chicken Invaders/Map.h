#pragma once
#include <vector>
#include <iostream>
#include"enemy.h"


class Map
{
	//This is actually private but for testing purposes, we made it public
public:
	//For any type of movement on the horizontal axis move 2 positions instead of one
	//Same for collision detection
	std::vector<std::string> map = {
		"##################################################################",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##                                                              ##",
		"##################################################################"
	};
public:
	void Redraw();
	void placeObject(enemy& newEnemy);
	bool MoveChar(std::pair<int, int> previousPos, std::pair<int, int> newPos, char chToDraw);
	void MoveEnemy(enemy& newEnemy,std::pair<int, int> startPos, std::pair<int, int> endPos, char chToDraw);
	
};