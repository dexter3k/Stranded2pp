#include "FileSystem.h"

#include <cassert>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/*

See stat(2) for documentation on what's happening here
$ man 2 stat
or
http://linux.die.net/man/2/stat

*/

namespace fs
{
	using Directory = DIR;
	using DirectoryEntry = struct dirent;
	using FileStatus = struct stat;

	void scanFolder(std::string const & pathToFolder, std::vector<std::string> & results)
	{
		Directory * directory = opendir(pathToFolder.c_str());

		for (DirectoryEntry * entry = readdir(directory); entry != nullptr; entry = readdir(directory)) {
			results.push_back(std::string(entry->d_name));
		}

		closedir(directory);
	}

	bool checkFolderExists(std::string const & pathToFolder)
	{
		FileStatus status;

		int error = stat(pathToFolder.c_str(), &status);
		return (error == 0) && ((status.st_mode & S_IFMT) == S_IFDIR);
	}

	bool checkFileExists(std::string const & pathToFile)
	{
		FileStatus status;

		int error = stat(pathToFile.c_str(), &status);
		return (error == 0) && ((status.st_mode & S_IFMT) == S_IFREG);
	}

	std::size_t getFileSize(std::string const & pathToFile)
	{
		std::ifstream file(pathToFile, std::ios::binary | std::ios::ate);
		if (!file) {
			std::cout << "Unable to open file: '" << pathToFile << "'" << std::endl;
			return false;
		}

		auto size = file.tellg();
		file.seekg(0, std::ios::beg);

		return static_cast<std::size_t>(size);
	}

	bool loadFile(std::string const & pathToFile, ByteBuffer & buffer)
	{
		std::ifstream file(pathToFile, std::ios::binary | std::ios::ate);
		if (!file) {
			std::cout << "Unable to open file: '" << pathToFile << "'" << std::endl;
			return false;
		}

		std::size_t size = static_cast<std::size_t>(file.tellg());
		file.seekg(0, std::ios::beg);

		assert(buffer.bytesLeftForWriting() >= size);

		std::vector<uint8_t> tempBuffer(size);
		if (!file.read(reinterpret_cast<char *>(tempBuffer.data()), tempBuffer.size())) {
			std::cout << "Unable to read file '" << pathToFile << "'" << std::endl;
			return false;
		}

		buffer.write(tempBuffer.data(), tempBuffer.size());

		return true;
	}

	bool loadFile(std::string const & pathToFile, RingBuffer & buffer)
	{
		std::ifstream file(pathToFile, std::ios::in | std::ifstream::binary);
		if (!file) {
			std::cout << "Unable to open file: '" << pathToFile << "'" << std::endl;
			return false;
		}

		file.seekg(0, std::ios::end);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		// TODO
		// For now just assertion
		assert(buffer.getFreeSpace() >= static_cast<unsigned>(size));

		std::vector<char> tempBuffer(size);
		if (!file.read(tempBuffer.data(), size)) {
			std::cout << "Unable to read file '" << pathToFile << "'" << std::endl;
			return false;
		}

		buffer.write(tempBuffer.data(), tempBuffer.size());

		return true;
	}
} // namespace fs
