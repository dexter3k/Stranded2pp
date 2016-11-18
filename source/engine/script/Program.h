#pragma once

#include <string>

namespace script
{

class ExecutionContext;

class Program
{
public:
	Program(ExecutionContext* context);

	void execute(const std::string& event);

	bool compile(const std::string& code);
private:
	bool tokenize(const std::string& code);
private:
	ExecutionContext* context;
};

} // namespace script
