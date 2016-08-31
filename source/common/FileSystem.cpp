#include "FileSystem.h"

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
} // namespace fs
