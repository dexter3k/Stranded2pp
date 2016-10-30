#include "StringUtils.h"

#include <algorithm>

namespace string
{
	std::string& trimLeft(std::string& string)
	{
		string.erase(
			string.begin(),
			std::find_if(
				string.begin(),
				string.end(),
				std::not1(
					std::ptr_fun<int, int>(std::isspace))));

		return string;
	}

	std::string& trimRight(std::string& string)
	{
		string.erase(
			std::find_if(
				string.rbegin(),
				string.rend(),
				std::not1(
					std::ptr_fun<int, int>(
						std::isspace))
				).base(),
			string.end());

		return string;
	}

	std::string& trim(std::string& string)
	{
		return trimLeft(trimRight(string));
	}

	bool startsWith(std::string& string, const std::string& text)
	{
		return string.substr(0, text.size()) == text;
	}
} // namespace string
