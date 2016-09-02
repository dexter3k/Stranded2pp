#pragma once

#include <string>

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
	static const std::string settingsConfigPath;
private:
	bool loadConfiguration();
private:
	std::string modificationName;

	bool isInitialized;
};
