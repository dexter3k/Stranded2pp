#pragma once

#include <string>

#include "common/RingBuffer.h"

namespace fs
{
	bool checkFolderExists(const std::string& pathToFolder);
	bool checkFileExists(const std::string& pathToFile);

	bool loadFile(const std::string& pathToFile, RingBuffer& buffer);
} // namespace fs
