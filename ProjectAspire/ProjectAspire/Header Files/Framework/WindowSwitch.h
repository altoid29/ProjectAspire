#pragma once

#include "../Include.h"

class WindowSwitch
{
public:
	Vector2 size{};
	int currentSubTab = 0;

	void Add( Vector2 position, float sizeY, const std::string name, std::vector<std::string>tabs, int* currentTab );
};