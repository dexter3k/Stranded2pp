#include "ObjectBuilder.h"

#include <iostream>

#include "common/FileSystem.h"
#include "utils/ParseUtils.h"
#include "utils/StringUtils.h"

namespace engine
{

// ObjectBuilder::ObjectBuilder(std::string const & modBasePath) :
// 	objects()
// {
// 	loadObjects(modBasePath);
// }

// void ObjectBuilder::loadObjects(std::string const & modBasePath)
// {
// 	std::vector<std::string> entries;
// 	fs::scanFolder(modBasePath + "sys/", entries);

// 	for (auto const & entry : entries) {
// 		if (string::startsWith(entry, "objects")
// 			&& string::endsWith(entry, ".inf"))
// 		{
// 			if (!parseObjectConfig(modBasePath + "sys/" + entry)) {
// 				throw std::runtime_error(
// 					std::string("Unable to parse config: sys/") + entry);
// 			}

// 			std::cout << "'sys/" << entry << "' is loaded successfully" << std::endl;
// 		}
// 	}
// }

// bool ObjectBuilder::parseObjectConfig(std::string const & filename)
// {
// 	std::vector<parser::inf::Entry> entries;
// 	if (!parser::inf::loadAndTokenize(filename, entries)) {
// 		return false;
// 	}

// 	unsigned currentId = unsigned(-1);
// 	for (auto const & entry : entries) {
// 		if (entry.key != "id" && currentId == unsigned(-1)) {
// 			throw std::runtime_error("Assigning values for unknown ID!");
// 		}

// 		if (entry.key == "id") {
// 			currentId = std::stoi(entry.value);
// 			if (currentId > objectTypeCount) {
// 				throw std::runtime_error(
// 					std::string("Expecting id in the range [1, ")
// 					+ std::to_string(objectTypeCount) + "]. Got: "
// 					+ std::to_string(currentId));
// 			}

// 			currentId = currentId - 1; // Start with 0, not 1

// 			if (objects[currentId].name != "") {
// 				throw std::runtime_error(
// 					std::string("ID " + std::to_string(currentId+1)
// 					+ " is already used for object: "
// 					+ objects[currentId].name));
// 			}

// 			objects[currentId].id = currentId;
// 		} else if (entry.key == "const") {
// 			// TODO
// 		} else if (entry.key == "name") {
// 			objects[currentId].name = entry.value;
// 		} else if (entry.key == "icon") {
// 			// TODO
// 		} else if (entry.key == "model") {
// 			objects[currentId].modelName = entry.value;
// 		} else if (entry.key == "x") {
// 			// TODO
// 		} else if (entry.key == "y") {
// 			// TODO
// 		} else if (entry.key == "z") {
// 			// TODO
// 		} else if (entry.key == "scale") {
// 			// TODO
// 		} else if (entry.key == "r") {
// 			// TODO
// 		} else if (entry.key == "g") {
// 			// TODO
// 		} else if (entry.key == "b") {
// 			// TODO
// 		} else if (entry.key == "color") {	
// 			// TODO
// 		} else if (entry.key == "fx") {
// 			// TODO
// 		} else if (entry.key == "autofade") {
// 			// TODO
// 		} else if (entry.key == "alpha") {
// 			// TODO
// 		} else if (entry.key == "shine") {
// 			// TODO
// 		} else if (entry.key == "detailtex") {
// 			// TODO
// 		} else if (entry.key == "col") {
// 			// TODO
// 		} else if (entry.key == "mat") {
// 			// TODO
// 		} else if (entry.key == "health") {
// 			// TODO
// 		} else if (entry.key == "healthchange") {
// 			// TODO
// 		} else if (entry.key == "swayspeed") {
// 			// TODO
// 		} else if (entry.key == "swaypower") {
// 			// TODO
// 		} else if (entry.key == "maxweight") {
// 			// TODO
// 		} else if (entry.key == "state") {
// 			// TODO
// 		} else if (entry.key == "behaviour") {
// 			// TODO
// 		} else if (entry.key == "script") {
// 			// TODO
// 		} else if (entry.key == "findratio") {
// 			// TODO
// 		} else if (entry.key == "find") {
// 			// TODO
// 		} else if (entry.key == "spawn") {
// 			// TODO
// 		} else if (entry.key == "description") {
// 			// TODO
// 		} else if (entry.key == "editor") {
// 			// TODO
// 		} else if (entry.key == "param") {
// 			// TODO
// 		} else if (entry.key == "growtime") {
// 			// TODO
// 		} else if (entry.key == "var") {
// 			// TODO
// 		} else if (entry.key == "group") {
// 			// TODO
// 		} else {
// 			std::cout << filename << ":" << entry.key << ": " << "Unknown key" << std::endl;

// 			return false;
// 		}
// 	}

// 	return true;
// }

} // namespace engine
