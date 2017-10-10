#include "Program.h"

#include <algorithm>

namespace script
{

bool Program::hasHandlerForEvent(std::string const & event)
{
	return std::find(std::begin(eventHandlers), std::end(eventHandlers), event) != std::end(eventHandlers);
}

} // namespace script
