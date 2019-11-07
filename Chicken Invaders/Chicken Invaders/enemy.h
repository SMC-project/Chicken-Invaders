#pragma once
#include<iostream>


class enemy
{
public:
	std::pair<int, int> m_previousPos;
	std::pair<int, int> m_newPos;
	char m_c;

public:
	enemy(std::pair<int, int> newPos, char c);
	
	
};

