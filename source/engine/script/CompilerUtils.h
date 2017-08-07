#pragma once

#include <list>
#include <string>

#include "Token.h"

namespace script
{
	std::list<script::Token> tokenize(std::string const& source);
} // namespace script
