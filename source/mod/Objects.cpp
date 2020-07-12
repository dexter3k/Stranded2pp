#include "Objects.h"

#include <stdexcept>
#include <iostream>
#include <vector>

#include "common/FileSystem.h"
#include "utils/ParseUtils.h"
#include "utils/StringUtils.h"

namespace
{

bool parseFile(std::string const & path, std::string const & filename, mod::Objects & objects)
{
	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(path + filename, entries))
		return false;

	unsigned currentId = unsigned(-1);
	for (auto const & entry : entries) {
		if (entry.key == "id") {
			currentId = std::stoi(entry.value);
			if (currentId > 1024) {
				throw std::runtime_error(
					std::string("Expecting id in the range [1, ")
					+ std::to_string(1024) + "]. Got: "
					+ std::to_string(currentId));
			}
			if (objects[currentId].name != "") {
				throw std::runtime_error(
					std::string("ID " + std::to_string(currentId+1)
					+ " is already used for object: "
					+ objects[currentId].name));
			}

			objects[currentId].id = currentId+1;
		} else if (entry.key == "const") {
			// TODO
		} else if (entry.key == "name") {
			objects[currentId].name = entry.value;
		} else if (entry.key == "icon") {
			objects[currentId].iconName = entry.value;
		} else if (entry.key == "model") {
			objects[currentId].modelName = entry.value;
		} else if (entry.key == "x") {
			objects[currentId].size.x = std::stof(entry.value);
		} else if (entry.key == "y") {
			objects[currentId].size.y = std::stof(entry.value);
		} else if (entry.key == "z") {
			objects[currentId].size.z = std::stof(entry.value);
		} else if (entry.key == "scale") {
			// TODO
		} else if (entry.key == "r") {
			objects[currentId].color.setRed(std::stoi(entry.value));
		} else if (entry.key == "g") {
			objects[currentId].color.setGreen(std::stoi(entry.value));
		} else if (entry.key == "b") {
			objects[currentId].color.setBlue(std::stoi(entry.value));
		} else if (entry.key == "color") {
			// TODO
		} else if (entry.key == "fx") {
			objects[currentId].fx = std::stoi(entry.value);
		} else if (entry.key == "autofade") {
			objects[currentId].autofade = std::stoi(entry.value);
		} else if (entry.key == "alpha") {
			objects[currentId].alpha = std::stof(entry.value);
		} else if (entry.key == "shine") {
			objects[currentId].shininess = std::stof(entry.value);
		} else if (entry.key == "detailtex") {
			objects[currentId].detailTextureName = entry.value;
			string::trim(objects[currentId].detailTextureName);
		} else if (entry.key == "col") {
			objects[currentId].collisionMode = std::stoi(entry.value);
		} else if (entry.key == "mat") {
			objects[currentId].material = mod::Material::fromString(entry.value);
		} else if (entry.key == "health") {
			objects[currentId].health = std::stof(entry.value);
			objects[currentId].healthChange = objects[currentId].health / 10.0f;
		} else if (entry.key == "healthchange") {
			objects[currentId].healthChange = std::stof(entry.value);
		} else if (entry.key == "swayspeed") {
			objects[currentId].swaySpeed = std::stof(entry.value);
			objects[currentId].active = true;
		} else if (entry.key == "swaypower") {
			objects[currentId].swayPower = std::stof(entry.value);
			objects[currentId].active = true;
		} else if (entry.key == "maxweight") {
			objects[currentId].maxWeight = std::stoi(entry.value);
		} else if (entry.key == "state") {
			// TODO
		} else if (entry.key == "behaviour") {
			objects[currentId].behaviour = entry.value;
		} else if (entry.key == "script") {
			objects[currentId].script += entry.value + '\n';
		} else if (entry.key == "findratio") {
			objects[currentId].searchRatio = std::stof(entry.value);
		} else if (entry.key == "find") {
			// TODO
		} else if (entry.key == "spawn") {
			// TODO
		} else if (entry.key == "description") {
			objects[currentId].description += entry.value + '\n';
		} else if (entry.key == "editor") {
			// TODO
		} else if (entry.key == "param") {
			// TODO
		} else if (entry.key == "growtime") {
			// TODO
		} else if (entry.key == "var") {
			// TODO
		} else if (entry.key == "group") {
			// TODO
		} else {
			std::cout << filename << ":" << entry.key << ": " << "Unknown key" << std::endl;

			return false;
		}
	}

	std::cout << "'" << filename << "' is loaded successfully" << std::endl;

	return true;
}

} // anonymous namespace

namespace mod
{

Objects loadObjects(std::string const & modPath)
{
	Objects objects;

	std::vector<std::string> entries;
	fs::scanFolder(modPath + "sys/", entries);

	for (auto const & entry : entries) {
		if (string::startsWith(entry, "objects")
			&& string::endsWith(entry, ".inf"))
		{
			if (!parseFile(modPath, std::string("sys/") + entry, objects))
				throw std::runtime_error(std::string("Unable to load game config"));
		}
	}

	return objects;
}

} // namespace mod
