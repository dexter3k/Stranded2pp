#pragma once

#include <array>
#include <string>

#include "math/Vector3.h"

namespace mod
{

struct GameConfig
{
	bool menuAdventure = true;
	bool menuRandom = true;
	bool menuLoadsave = true;
	bool menuSingleplayer = true;
	bool menuMultiplayer = true;
	bool menuEditor = true;
	bool menuCredits = true;

	int healthSystem;

	math::Vector3f exhaustMove;
	math::Vector3f exhaustSwim;
	math::Vector3f exhaustJump;
	math::Vector3f exhaustAttack;
	math::Vector3f exhaustedDamage;

	int diveTime = 8000;
	float diveDamage = 1;

	std::string defaultItemModel;
	int projectileLifetime = 15 * 1000;

	int fireRange = 50;
	int fireLightSize = 50;
	uint8_t fireLightBrightness = 150;

	int digTime = 2500;
	int fishTime = 2500;

	int jumpTime = 2500;
	float jumpFactor = 1.7;

	int fallTime = 850;
	float fallDamage = 1000;
	float fallDamageMinHeight = 100;
	float fallDamageMaxHeight = 3000;

	int rainRate = 15;
	int snowRate = 45;

	bool gore;

	int waveRate = 5000;
	int waveSpaceMin = 300;

	int combiScreen = 2;
	bool showEmptyBuildingGroups = false;

	int scriptLoopTimeout;
	std::string script;

	bool hasScriptKeys = false;
	std::array<int, 21> scriptKeys;

	unsigned objectLimit = 255;
	unsigned unitLimit = 100;
	unsigned itemLimit = 255;
};

GameConfig loadGameConfig(std::string const & modPath);

} // namespace mod
