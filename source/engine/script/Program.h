#pragma once

#include <string>
#include <vector>

namespace script
{

class Program
{
public:
	Program();
	Program(Program const& other);
	Program(Program && other);

	Program & operator=(Program const& other);
	Program & operator=(Program && other);

	bool getIsAssembled() const;
private:
	bool isAssembled;
};

} // namespace script
