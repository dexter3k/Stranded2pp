#pragma once

#include <string>
#include <vector>

#include "common/RingBuffer.h"

namespace fs
{
	void scanFolder(const std::string& pathToFolder,
		std::vector<std::string>& results);

	bool checkFolderExists(const std::string& pathToFolder);
	bool checkFileExists(const std::string& pathToFile);

	size_t getFileSize(const std::string& pathToFile);
	bool loadFile(const std::string& pathToFile, RingBuffer& buffer);
} // namespace fs
