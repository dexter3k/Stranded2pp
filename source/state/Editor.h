#pragma once

#include "State.h"

namespace state
{

class Editor : public State
{
	typedef State super;
public:
	Editor(Stranded & game);
};

} // namespace state
