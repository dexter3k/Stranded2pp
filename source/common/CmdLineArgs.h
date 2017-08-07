#pragma once

#include <string>
#include <vector>

namespace common
{

class CmdLineArgs
{
public:
	CmdLineArgs(std::vector<std::string> const & arguments);

	bool shouldForceWindowedMode() const { return forceWindowedMode; };
	bool shouldUseDebugMode() const { return debugMode; };
	std::string modificationName() const;
private:
	void parseArguments(std::vector<std::string> const & arguments);

	std::string parseStringParameter(std::vector<std::string> const & arguments, unsigned & i) const;
private:
	static std::string const defaultModification;

	bool forceWindowedMode;
	bool debugMode;
	std::string customModification;
};

} // namespace common
