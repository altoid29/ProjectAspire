#pragma once

#include "../Include.h"

class HotkeySwitch
{
public:
	float x, y;
	const char* selectedKeyName = "";
	int* keyValue = nullptr;
	bool waitingForKey = false;
	std::string name = "";

	void Add( float x, float y, std::string name, int* key );
	void Handle();
};