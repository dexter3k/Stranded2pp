#include "Lightcycle.h"

#include <iostream>
#include <stdexcept>

#include "common/FileSystem.h"
#include "utils/ParseUtils.h"
#include "utils/StringUtils.h"

namespace
{

gfx::Color parseColor(std::string const & value)
{
	auto const splits = string::split(value, ',');
	if (splits.size() < 3) {
		throw std::runtime_error(std::string("Unable to load lightcycle"));
	}

	return gfx::Color(std::stoi(splits[0]), std::stoi(splits[1]), std::stoi(splits[2]));
}

} // anonymous namespace

namespace mod
{

std::array<gfx::Color, 24> loadLightcycle(std::string const & modPath)
{
	std::string const filename = "sys/lightcycle.inf";
	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(modPath + filename, entries))
		throw std::runtime_error(std::string("Unable to load lightcycle"));

	std::array<gfx::Color, 24> cycle;
	for (auto const & entry : entries) {
		int key = std::stoi(entry.key);
		if (key < 0 || key > 23) {
			throw std::runtime_error(
				std::string("Invalid lightcycle key: ")
				+ std::to_string(key));
		}

		cycle[key] = parseColor(entry.value);
	}

	std::cout << "'" << filename << "' is loaded successfully" << std::endl;

	return cycle;
}

} // namespace mod
