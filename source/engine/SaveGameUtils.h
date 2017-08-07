#pragma once

#include <string>

class Engine;

namespace save
{
	bool loadFromFile(const std::string& filename, Engine& engine);
} // namespace save
