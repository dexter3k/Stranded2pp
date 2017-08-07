#include <iostream>
#include <string>
#include <vector>

#include "Stranded.h"

int main(int argc, char * argv[])
try {
	std::vector<std::string> arguments(argv + 1, argv + argc);

	Stranded game(arguments);
	game.run();

	return 0;
} catch (...) {
	std::cout << "Uncaught exception in main" << std::endl;

	throw;
}
