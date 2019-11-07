#pragma once
#include"Map.h"
#include<vector>
#include<iostream>
#include<string>
class Wave
{
public :
	void chickenWave(Map& myMap);
	void planetWave(Map& myMap,std::vector<std::string>planet);
private:
	std::vector<char> line;
	std::vector < std::string> planet = {
		"##                         @@@@@@@                              ##",
		"##                       @@@@@@@@@@@                            ##",
		"##                     @@@@@@@@@@@@@@@                          ##",
		"##                   @@@@@@@@@@@@@@@@@@@                        ##",
		"##                   @@@@@@@@@@@@@@@@@@@                        ##",
		"##                   @@@@@@@@@@@@@@@@@@@                        ##",
		"##                     @@@@@@@@@@@@@@@                          ##",
		"##                       @@@@@@@@@@@                            ##",
		"##                         @@@@@@@                              ##",
	};
};

