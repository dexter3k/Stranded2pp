#include "FileSystem.h"

#include <cassert>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>

/*

See stat(2) for documentation on what's happening here
$ man 2 stat
or
http://linux.die.net/man/2/stat

*/

namespace fs
{
	using FileStatus = struct stat;

	bool checkFolderExists(const std::string& pathToFolder)
	{
		FileStatus status;

		int error = stat(pathToFolder.c_str(), &status);
		return (error == 0) && ((status.st_mode & S_IFMT) == S_IFDIR);
	}

	bool checkFileExists(const std::string& pathToFile)
	{
		FileStatus status;

		int error = stat(pathToFile.c_str(), &status);
		return (error == 0) && ((status.st_mode & S_IFMT) == S_IFREG);
	}

	bool loadFile(const std::string& pathToFile, RingBuffer& buffer)
	{
		//std::cout << "Opening file '" << pathToFile << "'" << std::endl;

		std::ifstream file(pathToFile, std::ios::in | std::ifstream::binary);
		if (!file)
		{
			std::cout << "Unable to open file!" << std::endl;
			return false;
		}

		file.seekg(0, std::ios::end);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		// TODO
		// For now just assertion
		assert(buffer.getFreeSpace() >= static_cast<unsigned>(size));

		std::vector<char> tempBuffer(size);
		if (!file.read(tempBuffer.data(), size))
		{
			std::cout << "Unable to read file '" << pathToFile << "'" <<
				std::endl;
		}

		buffer.write(tempBuffer.data(), tempBuffer.size());

		return true;
	}
} // namespace fs
