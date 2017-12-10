#include "States.h"

#include <iostream>

#include "common/FileSystem.h"
#include "utils/ParseUtils.h"

namespace mod
{

std::vector<State> loadStates(std::string const & modPath)
{
	std::string const filename = "sys/states.inf";
	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(modPath + filename, entries))
		throw std::runtime_error(std::string("Unable to load states"));

	std::vector<State> states(70); // actually 71, but last is impossible to set
	unsigned currentId = unsigned(-1);
	for (auto const & entry : entries) {
		if (entry.key == "id") {
			currentId = std::stoi(entry.value);
			if (currentId > 70) {
				throw std::runtime_error(
					std::string("Expecting id in the range [1, ")
					+ std::to_string(70) + "]. Got: "
					+ std::to_string(currentId));
			}
		} else if (entry.key == "const") {
			// TODO
		} else if (entry.key == "name") {
			states[currentId].name = entry.value;
		} else if (entry.key == "frame") {
			int value = std::stoi(entry.value);
			if (value < 0 || value > 30) {
				throw std::runtime_error(
					std::string("Unable to set State frame. Out of bounds:")
					+ entry.value);
			}
			states[currentId].frame = value;
		} else if (entry.key == "icon") {
			// TODO
		} else if (entry.key == "script") {
			if (currentId < 29) {
				throw std::runtime_error(
					std::string("Unable to set State script. State is reserved:")
					+ std::to_string(currentId));
			}
			states[currentId].script += entry.value + '\xa6';
		} else {
			std::cout << filename << ":" << entry.key << ": " << "Unknown key" << std::endl;

			throw std::runtime_error(std::string("Unable to load game states"));
		}
	}

	std::cout << "'" << filename << "' is loaded successfully" << std::endl;

	return states;
}

} // namespace mod
