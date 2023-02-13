#pragma once

#include "Include.h"

class Menu
{
public:
	int currentTab = 0;

	bool isOpened = true;
	void Render();
};

inline Menu g_menu{};