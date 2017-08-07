#pragma once

#include <string>
#include <vector>

#include "common/RingBuffer.h"

namespace fs
{
	void scanFolder(std::string const & pathToFolder, std::vector<std::string> & results);

	bool checkFolderExists(std::string const & pathToFolder);
	bool checkFileExists(std::string const & pathToFile);

	size_t getFileSize(std::string const & pathToFile);
	bool loadFile(std::string const & pathToFile, RingBuffer & buffer);
} // namespace fs
