#pragma once

#include <string>
#include <vector>

namespace cfg
{
	bool readFile(const std::string& filename,
		std::vector<std::vector<char>>& tokens);
	void writeFile(const std::string& filename,
		const std::vector<std::vector<char>>& tokens);
} // namespace cfg
