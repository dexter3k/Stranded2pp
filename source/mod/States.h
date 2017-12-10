#pragma once

#include <string>
#include <vector>

namespace mod
{

struct State
{
	std::string name;
	unsigned frame;
	std::string script;
};

std::vector<State> loadStates(std::string const & modPath);

} // namespace mod
