#pragma once

#include <string>

class Resources
{
public:
	Resources(std::string const & modificationName);

	std::string const & getModificationName() const { return modificationName; };
private:
	std::string modificationName;
};
