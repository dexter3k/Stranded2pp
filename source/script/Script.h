#pragma once

#include <string>
#include <vector>

namespace script
{

class Script
{
public:
	Script() = default;

	std::vector<std::string> const & getEventHandlers() const { return eventHandlers; };
	bool hasHandlerForEvent(std::string const & event);
private:
	std::vector<std::string> eventHandlers;
};

} // namespace script
