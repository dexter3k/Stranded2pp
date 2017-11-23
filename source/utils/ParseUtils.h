#pragma once

#include <utility>
#include <string>
#include <vector>

namespace parser
{
	namespace inf
	{
		struct Entry
		{
			enum PropertyType
			{
				Value,
				Multiline
			} type;

			std::string key;

			std::string value;
		};

		bool loadAndTokenize(const std::string& filename,
			std::vector<Entry>& data);
	} // namespace inf
} // namespace parser
