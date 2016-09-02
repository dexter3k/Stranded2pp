#include "Cfg.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

#include "common/RingBuffer.h"

namespace cfg
{
	static const std::string defaultExtension = ".cfg";

	bool readFile(const std::string& filename,
		std::vector<std::vector<char>>& tokens)
	{
		RingBuffer buffer(8);
		char temp[8] = {1, 2, 3, 4, 5, 6, 7, 8};
		buffer.write(temp, 3);
		buffer.write(temp, 7);
		buffer.write(temp, 0);
		buffer.write(temp, 2);
		buffer.debug();
#if 0
		// Check extension
		assert(filename.rfind(defaultExtension,
			(filename.size() - defaultExtension.size())) == 
				(filename.size() - defaultExtension.size()));
		try
		{
			std::ifstream file;
			// Setup exceptions
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			// Open the file
			file.open(filename, std::ios::in | std::ios::binary);

			// Determine file size
			file.seekg(0, file.end);
			int fileLength = file.tellg();
			file.seekg(0, file.beg);

			// Create temporary buffer
			std::shared_ptr<char> buffer(new char[fileLength],
				std::default_delete<char[]>());
			// Read the buffer
			file.read(buffer.get(), fileLength);

			// Check that file ends with \n

			// Parse the file
			unsigned tokenCount = 0;
			for (int i = 0; i < fileLength; ++i)
			{

			}
		}
		catch (std::ifstream::failure& exception)
		{
			std::cout << "Error: unable to open file '" << filename << "'\n" <<
				exception.what() << std::endl;

			return false;
		}
#endif
		return true;
	}

	void writeFile(const std::string& filename,
		const std::vector<std::string>& tokens)
	{}
} // namespace cfg
