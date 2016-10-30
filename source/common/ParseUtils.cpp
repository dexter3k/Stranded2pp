#include "ParseUtils.h"

#include <fstream>
#include <iostream>

#include "common/StringUtils.h"

namespace parser
{
	bool loadAndTokenizeInf(const std::string& filename,
		std::vector<std::pair<std::string, std::string>>& tokens)
	{
		std::ifstream file(filename);
		if (file)
		{
			std::string line;
			while (std::getline(file, line))
			{
				line = string::trimLeft(line);

				if (line.empty() ||
					line[0] == '#' ||
					line[0] == '\r' ||
					line[0] == '\n')
				{
					continue;
				}

				std::string keyString = line.substr(0, line.find('='));
				keyString = string::trim(keyString);

				std::string valueString = line.substr(line.find('=') + 1);
				valueString = string::trim(valueString);

				tokens.push_back(
					std::pair<std::string, std::string>(
						keyString,
						valueString));
			}

			file.close();
		}
		else
		{
			std::cout << "Unable to open file '" << filename << "'" << std::endl;
			return false;
		}

		return true;
	}
} // namespace parser
