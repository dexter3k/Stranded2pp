#pragma once

#include <array>
#include <string>

#include "StringIds.h"

class Modification;

class Strings
{
public:
	Strings(std::string const & modificationPath);

	std::string getMiscString(strings::MiscStringId id) const { return misc[id]; };
	std::string getMenuString(strings::MenuStringId id) const { return menu[id]; };
	std::string getEditorString(strings::EditorStringId id) const { return editor[id]; };
private:
	void loadStrings(std::string const & filename);
private:
	static std::string const filename;
private:
	std::array<std::string, 51> misc;
	std::array<std::string, 251> menu;
	std::array<std::string, 301> editor;
};
