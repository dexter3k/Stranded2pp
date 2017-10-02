#pragma once

#include <string>

class Engine;

namespace save
{
	bool loadFromFile(std::string const & filename, Engine & engine);
} // namespace save
