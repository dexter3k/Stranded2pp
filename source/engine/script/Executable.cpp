#include "Executable.h"

namespace script
{

Executable::Executable() :
	stringPool(),
	instructions(),
	isAssembled(false)
{}

Executable::Executable(std::vector<std::string> && stringPool,
		std::vector<script::Instruction> && instructions) :
	stringPool(stringPool),
	instructions(instructions),
	isAssembled(true)
{}

Executable::Executable(Executable const& other) :
	stringPool(other.stringPool),
	instructions(other.instructions)
	isAssembled(other.isAssembled)
{}

Executable::Executable(Executable && other) :
	stringPool(std::move(other.stringPool)),
	instructions(std::move(other.instructions)),
	isAssembled(other.isAssembled)
{}

Executable & Executable::operator=(Executable const& other)
{
	stringPool = other.stringPool;
	instructions = other.instructions;
	isAssembled = other.isAssembled;
}

Executable & Executable::operator=(Executable && other)
{
	stringPool = std::move(other.stringPool);
	instructions = std::move(other.instructions);
	isAssembled = other.isAssembled;
}

bool Executable::getIsAssembled() const
{
	return isAssembled;
}

std::vector<std::string> const& Executable::getStringPool() const
{
	return stringPool;
}

std::vector<script::Instruction> const& Executable::getInstructions() const
{
	return instructions;
}

} // namespace script
