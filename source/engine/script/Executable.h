#pragma once

#include "Instruction.h"

namespace script
{

class Executable
{
public:
	Executable();
	Executable(Executable const& other);
	Executable(Executable && other);

	Executable & operator=(Executable const& other);
	Executable & operator=(Executable && other);

	bool getIsAssembled() const;

	std::vector<std::string> const& getStringPool() const;

	std::vector<script::Instruction> const& getInstructions() const;
private:
	Executable(std::vector<std::string> && stringPool,
		std::vector<script::Instruction> && instructions);
private:
	std::vector<std::string> stringPool;
	std::vector<script::Instruction> instructions;

	bool isAssembled;
};

} // namespace script
