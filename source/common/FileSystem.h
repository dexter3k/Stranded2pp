#pragma once

#include <string>

namespace fs
{
	bool checkFolderExists(const std::string& pathToFolder);
	bool checkFileExists(const std::string& pathToFile);
} // namespace fs
