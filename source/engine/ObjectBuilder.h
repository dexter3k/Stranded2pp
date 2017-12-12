#pragma once

#include <string>
#include <array>

// #include "mod/Object.h"

namespace engine
{

class ObjectBuilder
{
public:
	ObjectBuilder(std::string const & modBasePath);
private:
	void loadObjects(std::string const & modBasePath);
	bool parseObjectConfig(std::string const & filename);

	static unsigned const objectTypeCount = 1024;

	// std::array<mod::Object, objectTypeCount> objects;
};

} // namespace engine
