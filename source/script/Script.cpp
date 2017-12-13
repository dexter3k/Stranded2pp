#include "Script.h"

namespace script
{

bool Script::hasHandlerForEvent(std::string const & event)
{
	return std::find(std::begin(eventHandlers), std::end(eventHandlers), event) != std::end(eventHandlers);
}

} // namespace script
