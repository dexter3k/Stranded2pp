#include "ParseUtils.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "utils/StringUtils.h"

namespace parser
{
	namespace inf
	{
		bool loadAndTokenize(const std::string& filename,
			std::vector<Entry>& data)
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

					if (keyString == "script"
						|| keyString == "description")
					{
						if (valueString == "start")
						{
							std::string multiline = "";

							while (std::getline(file, line))
							{
								keyString = line.substr(0, line.find('='));
								keyString = string::trim(keyString);
								valueString = line.substr(line.find('=') + 1);
								valueString = string::trim(valueString);

								if ((keyString == "script" || keyString == "description")
									&& valueString == "end")
								{
									break;	
								}

								multiline = multiline + "\n" + line;
							}

							Entry entry;
							entry.type = Entry::Multiline;
							entry.key = keyString;
							entry.value = multiline;
							data.push_back(entry);

							continue;
						}
						else
						{
							std::cout << filename << ": " << "expected 'start'"
								<< std::endl;

							return false;
						}
					}

					Entry entry;
					entry.type = Entry::Value;
					entry.key = keyString;
					entry.value = valueString;
					data.push_back(entry);
				}

				file.close();
			}
			else
			{
				std::cout << "Unable to open file '" << filename << "'" <<
					std::endl;

				return false;
			}

			return true;
		}
	} // namespace inf
} // namespace parser
