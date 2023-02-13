#pragma once

#include "../Include.h"

class SelectionSwitch
{
public:
	float x, y;
	int* currentItem = nullptr;
	std::vector<std::string>items;
	std::string name = "";

	void Add( float x, float y, std::string name, int* currentItem, std::vector<std::string>items );
	void Handle();
};