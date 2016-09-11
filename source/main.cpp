#include <string>
#include <vector>
#include <iostream>

#include "Stranded.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> arguments;
	for (int i = 1; i < argc; ++i)
	{
		arguments.push_back(std::string(argv[i]));
	}

	Stranded game;
	if (game.init(arguments))
	{
		game.run();
	}
	
	return 0;
}
