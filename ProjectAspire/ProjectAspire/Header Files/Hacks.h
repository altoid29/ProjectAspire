#pragma once

#include "Include.h"

class HudRelated
{
public:
	void RevealSpectators();
};

class ESPRelated
{
public:
	void Handle();
};

class TriggerbotRelated
{
public:
	void Handle();
};

class ProjectileRelated
{
public:
	void Handle();
};

class AimbotRelated
{
public:
	void VisualizeFOVRadius();
	Player* GetBestPlayer();
	void Handle();
};

inline HudRelated g_hud{};
inline ESPRelated g_esp{};
inline TriggerbotRelated g_triggerbot{};
inline ProjectileRelated g_projectiles{};
inline AimbotRelated g_aimbot{};