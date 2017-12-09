#include "Compiler.h"

#include <iostream>

#include "CompilerUtils.h"

namespace script
{
	Program compile(std::string const & source)
	{
		Program program;

		auto tokens = tokenize(source);
		if (tokens.empty()) {
			return program;
		}

		return program;
	}
} // namespace script
