#include "Program.h"

#include <cctype>
#include <algorithm>
#include <iostream>

#include "ExecutionContext.h"

namespace script
{

Program::Program() :
	isAssembled(false)
{}

Program::Program(Program const& other) :
	isAssembled(other.isAssembled)
{}

Program::Program(Program && other) :
	isAssembled(other.isAssembled)
{}

Program & Program::operator=(Program const& other)
{
	isAssembled = other.isAssembled;

	return *this;
}

Program & Program::operator=(Program && other)
{
	isAssembled = other.isAssembled;

	return *this;
}

bool Program::getIsAssembled() const
{
	return isAssembled;
}

} // namespace script
