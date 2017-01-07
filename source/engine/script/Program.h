#pragma once

#include <list>
#include <string>

#include "Token.h"

namespace script
{

class ExecutionContext;

class Program
{
public:
	Program(ExecutionContext* context);

	void execute(std::string const& event);

	bool compile(std::string const& code);
private:
	std::list<script::Token> tokenize(std::string const& code) const;
private:
	ExecutionContext* context;
};

} // namespace script
