#include "GameConfig.h"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "common/FileSystem.h"
#include "utils/ParseUtils.h"
#include "utils/StringUtils.h"

namespace
{

bool parseVector3f(std::string const & value, math::Vector3f & vector)
{
	auto const splits = string::split(value, ',');
	if (splits.size() < 3) {
		return false;
	}

	vector.x = std::stof(splits[0]);
	vector.y = std::stof(splits[1]);
	vector.z = std::stof(splits[2]);

	return true;
}

bool parseFile(std::string const & path, std::string const & filename, mod::GameConfig & config)
{
	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(path + filename, entries))
		return false;

	for (auto const & entry : entries) {
		if (entry.key == "healthsystem") {
			config.healthSystem = std::stoi(entry.value);
		} else if (entry.key == "exhaust_move") {
			if (!parseVector3f(entry.value, config.exhaustMove)) return false;
		} else if (entry.key == "exhaust_swim") {
			if (!parseVector3f(entry.value, config.exhaustSwim)) return false;
		} else if (entry.key == "exhaust_jump") {
			if (!parseVector3f(entry.value, config.exhaustJump)) return false;
		} else if (entry.key == "exhaust_attack") {
			if (!parseVector3f(entry.value, config.exhaustAttack)) return false;
		} else if (entry.key == "exhausted_damage") {
			if (!parseVector3f(entry.value, config.exhaustedDamage)) return false;
		} else if (entry.key == "dive_time") {
			config.diveTime = std::stoi(entry.value);
		} else if (entry.key == "dive_damage") {
			config.diveDamage = std::stof(entry.value);
		} else if (entry.key == "default_itemmodel") {
			config.defaultItemModel = entry.value;
		} else if (entry.key == "projectile_lifetime") {
			config.projectileLifetime = std::stoi(entry.value);
		} else if (entry.key == "firerange") {
			config.fireRange = std::stoi(entry.value);
		} else if (entry.key == "dig_time") {
			config.digTime = std::stoi(entry.value);
		} else if (entry.key == "fish_time") {
			config.fishTime = std::stoi(entry.value);
		} else if (entry.key == "jumptime") {
			config.jumpTime = std::stoi(entry.value);
		} else if (entry.key == "jumpfactor") {
			config.jumpFactor = std::stof(entry.value);
		} else if (entry.key == "rainratio") {
			config.rainRate = std::stoi(entry.value);
		} else if (entry.key == "snowratio") {
			config.snowRate = std::stoi(entry.value);
		} else if (entry.key == "gore") {
			config.gore = (std::stoi(entry.value) != 0);
		} else if (entry.key == "waverate") {
			config.waveRate = std::stoi(entry.value);
		} else if (entry.key == "minwavespace") {
			config.waveSpaceMin = std::stoi(entry.value);
		} else if (entry.key == "combiscreen") {
			config.combiScreen = std::stoi(entry.value);
		} else if (entry.key == "scriptlooptimeout") {
			config.scriptLoopTimeout = std::stoi(entry.value);
		} else if (entry.key == "script") {
			config.script += entry.value + '\xa6';
		} else if (entry.key == "scriptkey") {
			// TODO
		} else if (entry.key == "limit_objects") {
			int value = std::stoi(entry.value);
			if (value < 0) value = 1;
			config.objectLimit = value;
		} else if (entry.key == "limit_units") {
			int value = std::stoi(entry.value);
			if (value < 0) value = 1;
			config.unitLimit = value;
		} else if (entry.key == "limit_items") {
			int value = std::stoi(entry.value);
			if (value < 0) value = 1;
			config.itemLimit = value;
		} else if (entry.key == "menu_adventure") {
			config.menuAdventure = (std::stoi(entry.value) != 0);
		} else if (entry.key == "menu_random") {
			config.menuRandom = (std::stoi(entry.value) != 0);
		} else if (entry.key == "menu_loadsave") {
			config.menuLoadsave = (std::stoi(entry.value) != 0);
		} else if (entry.key == "menu_singleplayer") {
			config.menuSingleplayer = (std::stoi(entry.value) != 0);
		} else if (entry.key == "menu_multiplayer") {
			config.menuMultiplayer = (std::stoi(entry.value) != 0);
		} else if (entry.key == "menu_editor") {
			config.menuEditor = (std::stoi(entry.value) != 0);
		} else if (entry.key == "menu_credits") {
			config.menuCredits = (std::stoi(entry.value) != 0);
		} else if (entry.key == "firelightsize") {
			config.fireLightSize = std::stoi(entry.value);
		} else if (entry.key == "firelightbrightness") {
			int value = std::stoi(entry.value);
			if (value < 0) value = 0;
			if (value > 255) value = 255;
			config.fireLightBrightness = value;
		} else if (entry.key == "terrain_color_normal") {
			// TODO
		} else if (entry.key == "terrain_color_desert") {
			// TODO
		} else if (entry.key == "terrain_color_snow") {
			// TODO
		} else if (entry.key == "terrain_color_swamp") {
			// TODO
		} else if (entry.key == "showemptybuildinggroups") {
			config.showEmptyBuildingGroups = (std::stoi(entry.value) != 0);
		} else if (entry.key == "falltime") {
			config.fallTime = std::stoi(entry.value);
		} else if (entry.key == "falldamage") {
			config.fallDamage = std::stof(entry.value);
		} else if (entry.key == "falldamageminy") {
			config.fallDamageMinHeight = std::stof(entry.value);
		} else if (entry.key == "falldamagemaxy") {
			config.fallDamageMaxHeight = std::stof(entry.value);
		} else {
			std::cout << filename << ":" << entry.key << ": " << "Unknown key" << std::endl;

			return false;
		}
	}

	std::cout << "'" << filename << "' is loaded successfully" << std::endl;

	return true;
}

} // anonymous namespace

namespace mod
{

GameConfig loadGameConfig(std::string const & modPath)
{
	GameConfig config;

	std::vector<std::string> entries;
	fs::scanFolder(modPath + "sys/", entries);

	for (auto const & entry : entries) {
		if (string::startsWith(entry, "game")
			&& string::endsWith(entry, ".inf"))
		{
			if (!parseFile(modPath, std::string("sys/") + entry, config))
				throw std::runtime_error(std::string("Unable to load game config"));
		}
	}

	return config;
}

} // namespace mod
