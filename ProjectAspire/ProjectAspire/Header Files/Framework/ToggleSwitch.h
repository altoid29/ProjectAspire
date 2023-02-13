#pragma once

#include "../Include.h"

class ToggleSwitch
{
public:
	float x, y;
	bool* variable = nullptr;
	std::string name = "";

	void Add( float x, float y, std::string name, bool* variable );
	void Handle();
};