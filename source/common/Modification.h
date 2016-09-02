#pragma once

#include <string>

class RingBuffer;

class Modification
{
public:
	Modification();
	Modification(const std::string& modificationName);
	~Modification();

	bool init();

	void setName(const std::string& newModificationName);
	std::string getName() const;

	std::string getPath() const;
private:
	static const std::string defaultModificationPath;

	static const size_t configurationBufferSize;
	static const std::string controlsConfigPath;
	static const std::string scriptControlsConfigPath;
	static const std::string settingsConfigPath;
private:
	bool loadConfiguration();
	bool loadControls();
	bool loadScriptControls();
	bool loadSettings();
private:
	std::string modificationName;

	bool isInitialized;
};
