#include "Modification.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "common/FileSystem.h"
#include "common/RingBuffer.h"

const std::string Modification::defaultModificationPath = "mods/";

const size_t Modification::configurationBufferSize = 4096;

const std::string Modification::controlsConfigPath = "sys/controls.cfg";
const std::string Modification::scriptControlsConfigPath =
	"sys/scriptcontrols.cfg";
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
	return loadControls() &&
		loadScriptControls() &&
		loadSettings();
}

// TODO:
bool Modification::loadControls()
{
	RingBuffer buffer(configurationBufferSize);

	if (!fs::loadFile(getPath() + controlsConfigPath, buffer))
	{
		return false;
	}

	std::string tempString = "";

	// First string with warnign
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	for (unsigned i = 0; i < 22; ++i)
	{
		uint16_t tempValue = 0;
		if (!buffer.readUint16(tempValue)) return false;

		std::cout << "i: " << i << " " << tempValue << std::endl;
	}

	float tempFloat = 0.0f;
	if (!buffer.readFloat(tempFloat)) return false;

	std::cout << tempFloat << std::endl;

	bool tempBool = false;
	if (!buffer.readBool(tempBool)) return false;
	if (!buffer.readBool(tempBool)) return false;

	std::cout << "'" << controlsConfigPath << "' is loaded successfully" <<
		std::endl;

	return true;
}

// TODO:
bool Modification::loadScriptControls()
{
	RingBuffer buffer(configurationBufferSize);

	if (!fs::loadFile(getPath() + scriptControlsConfigPath, buffer))
	{
		return false;
	}

	std::string tempString = "";

	// First string with warnign
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	for (unsigned i = 0; i < 22; ++i)
	{
		uint16_t tempValue = 0;
		if (!buffer.readUint16(tempValue)) return false;

		std::cout << tempValue << std::endl;
	}

	std::cout << "'" << scriptControlsConfigPath << "' is loaded successfully" <<
		std::endl;

	return true;
}

bool Modification::loadSettings()
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

	// View range
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Terrain
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Water
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Sky
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Effects
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	// Music volume
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// SFX volume
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	// Grass
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// FX2D
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// FXLight
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Windsway
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	// Character name
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Default port (for dedicated server?)
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	// Fog
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// HWMultitexture
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Motionblur
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	// Motionblur alpha
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	std::cout << "'" << settingsConfigPath << "' is loaded successfully" <<
		std::endl;

	return true;
}
