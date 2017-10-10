#pragma once

#include <string>
#include <vector>

namespace script
{

class Program
{
public:
	Program() = default;
	Program(Program const & other) = default;

	std::vector<std::string> const & getEventHandlers() const { return eventHandlers; };
	bool hasHandlerForEvent(std::string const & event);
private:
	std::vector<std::string> eventHandlers;
};

} // namespace script
