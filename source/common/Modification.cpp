#include "Modification.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "common/FileSystem.h"
#include "common/RingBuffer.h"

const std::string Modification::defaultModificationPath = "mods/";

const size_t Modification::configurationBufferSize = 4096;
const std::string Modification::settingsConfigPath = "sys/settings.cfg";

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

	if (!loadConfiguration())
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

bool Modification::loadConfiguration()
{
	RingBuffer buffer(configurationBufferSize);

	if (!fs::loadFile(getPath() + settingsConfigPath, buffer))
	{
		return false;
	}

	std::string tempString = "";

	// First string with warnign
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	// Screen width
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Screen height
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Bits per pixel
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	if (!buffer.readNewlineTerminatedString(tempString)) return false;


	std::cout << "Config loaded!" << std::endl;
	return true;
}
