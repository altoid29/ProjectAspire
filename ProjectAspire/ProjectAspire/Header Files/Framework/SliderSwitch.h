#pragma once

#include "../Include.h"

class SliderSwitch
{
public:
	float x, y;
	int min, max;
	int* currentValue = nullptr;
	std::string name = "";

	void Add( float x, float y, std::string name, int* variable, int minimum, int maximum );
	void Handle();
};