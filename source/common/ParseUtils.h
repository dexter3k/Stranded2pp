#pragma once

#include <utility>
#include <string>
#include <vector>

namespace parser
{
	bool loadAndTokenizeInf(const std::string& filename,
		std::vector<std::pair<std::string, std::string>>& tokens);
} // namespace parser
