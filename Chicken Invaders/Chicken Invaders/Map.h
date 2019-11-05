#pragma once
#include <vector>
#include <iostream>

class Map
{
	//This is actually private but for testing purposes, we made it public
public:
	//For any type of movement on the horizontal axis move 2 positions instead of one
	//Same for collision detection
	std::vector<std::string> map = {
		"##################################################################",
		"##@                                                             ##",
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

	bool MoveChar(std::pair<int, int> previousPos, std::pair<int, int> newPos, char chToDraw);
};