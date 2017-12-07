#include "Modification.h"

#include <iostream>
#include <stdexcept>

#include "common/ByteBuffer.h"
#include "common/FileSystem.h"

const std::string Modification::defaultModificationPath = "mods/";

const std::string Modification::controlsConfigPath = "sys/controls.cfg";
const std::string Modification::scriptControlsConfigPath = "sys/scriptcontrols.cfg";
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

bool Modification::loadScriptControls()
{
	std::string const filename = getPath() + scriptControlsConfigPath;
	
	ByteBuffer buffer(fs::getFileSize(filename));
	if (!fs::loadFile(filename, buffer)) {
		return false;
	}

	try {
		buffer.readLine(); // Warning header

		for (unsigned i = 0; i < 21; ++i) {
			scriptControls.inputKeys[i] = buffer.readUint16();
		}
	} catch (std::runtime_error &) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": data error");
	}

	std::cout << "'" << scriptControlsConfigPath << "' is loaded successfully" << std::endl;

	return true;
}

bool Modification::loadSettings()
{
	std::string const filename = getPath() + settingsConfigPath;

	ByteBuffer buffer(fs::getFileSize(filename));
	if (!fs::loadFile(filename, buffer)) {
		return false;
	}

	buffer.readLine(); // Warning header

	try {
		settings.screen.width = std::stoi(buffer.readLine());
		settings.screen.height = std::stoi(buffer.readLine());
		settings.screen.bitsPerPixel = std::stoi(buffer.readLine());
	
		settings.viewRange = std::stoi(buffer.readLine());
		settings.terrain = std::stoi(buffer.readLine());
		settings.water = std::stoi(buffer.readLine());
		settings.sky = std::stoi(buffer.readLine());
		settings.effects = std::stoi(buffer.readLine());
	
		settings.musicVolume = std::stoi(buffer.readLine());
		settings.sfxVolume = std::stoi(buffer.readLine());
	
		settings.grass = std::stoi(buffer.readLine());
		settings.fx2d = std::stoi(buffer.readLine());
		settings.fxlight = std::stoi(buffer.readLine());
		settings.windsway = std::stoi(buffer.readLine());
	
		settings.playerName = buffer.readLine();
		settings.serverPort = std::stoi(buffer.readLine());
	
		settings.fog = std::stoi(buffer.readLine());
		settings.hwmultitex = std::stoi(buffer.readLine());
		settings.motionBlur = std::stoi(buffer.readLine());
		settings.motionBlurAplha = std::stoi(buffer.readLine());
	} catch (std::runtime_error &) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": data error");
	}

	std::cout << "'" << settingsConfigPath << "' is loaded successfully" << std::endl;

	return true;
}
