#include "Strings.h"

#include <iostream>

std::string const Strings::filename = "sys/strings.inf";

Strings::Strings(std::string const & modificationPath) :
	misc(),
	menu(),
	editor()
{
	loadStrings(modificationPath + filename);
}

void Strings::loadStrings(std::string const &)
{}
