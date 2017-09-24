#include "Strings.h"

#include <iostream>

#include "utils/ParseUtils.h"

std::string const Strings::filename = "sys/strings.inf";

Strings::Strings(std::string const & modificationPath) :
	misc(),
	menu(),
	editor()
{
	loadStrings(modificationPath + filename);
}

void Strings::loadStrings(std::string const & filename)
{
	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(filename, entries)) {
		throw std::runtime_error(std::string("Unable to load: ") + filename);
	}

	for (auto const & entry : entries) {
		if (entry.key.size() != 4) {
			std::cout << "Skipping malformed entry in " << filename
				<< ": " << entry.key << std::endl;
			continue;
		}

		unsigned id = std::stoi(entry.key.substr(1, 3));
		switch (entry.key[0]) {
		case '0':
			if (id < misc.size()) {
				misc[id] = entry.value;
				continue;
			}
			break;
		case 'm':
			if (id < menu.size()) {
				menu[id] = entry.value;
				continue;
			}
			break;
		case 'e':
			if (id < editor.size()) {
				editor[id] = entry.value;
				continue;
			}
			break;
		default:
			break;
		}

		std::cout << "Invalid string id in " << filename
			<< ": " << entry.key << std::endl;
	}
}
