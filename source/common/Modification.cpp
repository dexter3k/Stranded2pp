#include "Modification.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "common/Cfg.h"
#include "common/FileSystem.h"

const std::string Modification::defaultModificationPath = "mods/";

Modification::Modification() :
	modificationName(),
	isInitialized(false)
{}

Modification::Modification(const std::string& modificationName) :
	modificationName(modificationName),
	isInitialized(false)
{}

Modification::~Modification()
{}

bool Modification::init()
{
	// Check and load modification
	if (!fs::checkFolderExists(getPath()))
	{
		std::cout << "Error: mod '" << modificationName <<
			"' is missing from 'mods' folder!" << std::endl;

		return false;
	}

	std::vector<std::vector<char>> data;
	if (!cfg::readFile(getPath() + "sys/settingz.cfg", data))
	{
		return false;
	}

	isInitialized = true;

	std::cout << "Mod init finished" << std::endl;

	return true;
}

void Modification::setName(const std::string& newModificationName)
{
	assert(!isInitialized);

	modificationName = newModificationName;
}

std::string Modification::getName() const
{
	return modificationName;
}

std::string Modification::getPath() const
{
	return defaultModificationPath + modificationName + "/";
}
