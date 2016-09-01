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
private:
	std::string modificationName;

	bool isInitialized;
};
