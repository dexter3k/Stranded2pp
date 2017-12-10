#include "StringUtils.h"

#include <algorithm>
#include <functional>

namespace string
{
	std::vector<std::string> split(std::string const & string, char sep)
	{
		std::vector<std::string> slices;
		std::size_t start = 0;
		std::size_t end = 0;
		while ((end = string.find(sep, start)) != std::string::npos) {
			slices.push_back(string.substr(start, end - start));

			start = end + 1;
		}

		slices.push_back(string.substr(start));

		return slices;
	}

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

	bool startsWith(const std::string& string, const std::string& text)
	{
		return string.substr(0, text.size()) == text;
	}

	bool endsWith(const std::string& string, const std::string& text)
	{
		return (string.size() >= text.size()) &&
			(string.substr(string.size() - text.size()) == text);
	}

} // namespace string
