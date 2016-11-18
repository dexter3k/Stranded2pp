#include "Program.h"

#include <algorithm>
#include <iostream>

#include "ExecutionContext.h"

namespace script
{

Program::Program(ExecutionContext* context) :
	context(context)
{}

void Program::execute(const std::string& event)
{}

bool Program::compile(const std::string& code)
{
	// Replace all '¦' (166 in Western 1252) symbols with newline
	std::string prettified(code);
	std::replace(prettified.begin(), prettified.end(), char(166), '\n');

	//std::cout << "Compiling code: \n" << prettified << std::endl;

	return tokenize(prettified);
}

bool Program::tokenize(const std::string& code)
{
	return true;
}

} // namespace script
