#include "CmdLineArgs.h"

#include <stdexcept>

namespace common
{

std::string const CmdLineArgs::defaultModification = "Stranded II";

CmdLineArgs::CmdLineArgs(std::vector<std::string> const & arguments) :
	forceWindowedMode(false),
	debugMode(false),
	customModification("")
{
	parseArguments(arguments);
}

std::string CmdLineArgs::modificationName() const
{
	return customModification.empty() ? defaultModification : customModification;
}

void CmdLineArgs::parseArguments(std::vector<std::string> const & arguments)
{
	unsigned const argumentCount = arguments.size();
	for (unsigned i = 0; i < argumentCount; ++i) {
		if (arguments[i] == "-win")
			forceWindowedMode = true;
		else if (arguments[i] == "-debug")
			debugMode = true;
		else if (arguments[i] == "-mod")
			customModification = parseStringParameter(arguments, i);
		else
			throw std::runtime_error(std::string("Unknown argument: ") + arguments[i]);
	}
}

std::string CmdLineArgs::parseStringParameter(std::vector<std::string> const & arguments, unsigned & i) const
{
	if (++i >= arguments.size())
		throw std::runtime_error(std::string("Expected string parameter"));

	return arguments[i];
}

} // namespace common
