#include "Modification.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "common/ByteBuffer.h"
#include "common/FileSystem.h"
#include "common/RingBuffer.h"

const std::string Modification::defaultModificationPath = "mods/";

const size_t Modification::configurationBufferSize = 4096;

const std::string Modification::controlsConfigPath = "sys/controls.cfg";
const std::string Modification::scriptControlsConfigPath =
	"sys/scriptcontrols.cfg";
const std::string Modification::settingsConfigPath = "sys/settings.cfg";

Modification::Modification(std::string const & modificationName) :
	modificationName(modificationName),
	controls(),
	scriptControls(),
	settings()
{
	if (!init())
		throw std::runtime_error("Unable to initialize Modification");
}

bool Modification::init()
{
	// Check and load modification
	if (!fs::checkFolderExists(getPath())) {
		std::cout << "Error: mod '" << modificationName <<
			"' is missing from 'mods' folder!" << std::endl;

		return false;
	}

	if (!loadConfiguration()) {
		return false;
	}

	return true;
}

std::string Modification::getName() const
{
	return modificationName;
}

std::string Modification::getPath() const
{
	return defaultModificationPath + modificationName + "/";
}

Modification::Controls& Modification::getControls()
{
	return controls;
}

const Modification::Controls& Modification::getControls() const
{
	return controls;
}

Modification::ScriptControls& Modification::getScriptControls()
{
	return scriptControls;
}

const Modification::ScriptControls& Modification::getScriptControls() const
{
	return scriptControls;
}

Modification::Settings& Modification::getSettings()
{
	return settings;
}

const Modification::Settings& Modification::getSettings() const
{
	return settings;
}

bool Modification::loadConfiguration()
{
	return loadControls()
		&& loadScriptControls()
		&& loadSettings();
}

// TODO:
bool Modification::loadControls()
{
	std::string const filename = getPath() + controlsConfigPath;
	ByteBuffer buffer(fs::getFileSize(filename));

	if (!fs::loadFile(filename, buffer)) {
		return false;
	}

	try {
		buffer.readLine(); // Warning header

		for (unsigned i = 0; i < 21; ++i) {
			controls.inputKeys[i] = buffer.readUint16();
		}

		controls.mouse.sensitivity = buffer.readFloat();
		controls.mouse.invertVertically = buffer.readBool();
		controls.mouse.smooth = buffer.readBool();
	} catch (std::runtime_error &) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": data error");
	}

	std::cout << "'" << controlsConfigPath << "' is loaded successfully" << std::endl;

	return true;
}

// TODO:
bool Modification::loadScriptControls()
{
	RingBuffer buffer(configurationBufferSize);

	if (!fs::loadFile(getPath() + scriptControlsConfigPath, buffer)) {
		return false;
	}

	// First string with warnign
	std::string tempString = "";
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	for (unsigned i = 0; i < 21; ++i) {
		if (!buffer.readUint16(scriptControls.inputKeys[i])) return false;
	}

	std::cout << "'" << scriptControlsConfigPath << "' is loaded successfully" << std::endl;

	return true;
}

bool Modification::loadSettings()
{
	RingBuffer buffer(configurationBufferSize);

	if (!fs::loadFile(getPath() + settingsConfigPath, buffer)) {
		return false;
	}

	// First string with warnign
	std::string tempString = "";
	if (!buffer.readNewlineTerminatedString(tempString)) return false;

	// Screen width
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.screen.width = std::stoi(tempString);
	// Screen height
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.screen.height = std::stoi(tempString);
	// Bits per pixel
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.screen.bitsPerPixel = std::stoi(tempString);

	// View range
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.viewRange = std::stoi(tempString);
	// Terrain
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.terrain = std::stoi(tempString);
	// Water
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.water = std::stoi(tempString);
	// Sky
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.sky = std::stoi(tempString);
	// Effects
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.effects = std::stoi(tempString);

	// Music volume
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.musicVolume = std::stoi(tempString);
	// SFX volume
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.sfxVolume = std::stoi(tempString);

	// Grass
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.grass = std::stoi(tempString);
	// FX2D
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.fx2d = std::stoi(tempString);
	// FXLight
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.fxlight = std::stoi(tempString);
	// Windsway
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.windsway = std::stoi(tempString);

	// Character name
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.playerName = tempString;
	// Default port (for dedicated server?)
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.serverPort = std::stoi(tempString);

	// Fog
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.fog = std::stoi(tempString);
	// HWMultitexture
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.hwmultitex = std::stoi(tempString);
	// Motionblur
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.motionBlur = std::stoi(tempString);
	// Motionblur alpha
	if (!buffer.readNewlineTerminatedString(tempString)) return false;
	settings.motionBlurAplha = std::stoi(tempString);

	std::cout << "'" << settingsConfigPath << "' is loaded successfully" << std::endl;

	return true;
}
