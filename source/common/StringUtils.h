#pragma once

#include <string>

namespace string
{
	std::string& trimLeft(std::string& string);

	std::string& trimRight(std::string& string);

	std::string& trim(std::string& string);

	bool startsWith(std::string& string, const std::string& text);
} // namespace string
