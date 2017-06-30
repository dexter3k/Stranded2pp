#include <iostream>
#include <string>
#include <vector>

#include "Stranded.h"

int main(int argc, char * argv[])
{
	std::vector<std::string> arguments(argv + 1, argv + argc);

	Stranded game(arguments);
	game.run();

	return 0;
}
