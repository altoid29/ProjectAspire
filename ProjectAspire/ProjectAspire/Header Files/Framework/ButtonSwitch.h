#pragma once

#include "../Include.h"

class ButtonSwitch
{
public:
	float x, y;
	std::function<void()>callback;
	std::string name = "";

	void Add( float x, float y, std::string name, std::string buttonName, std::function<void()>callback );
	void Handle();
};