#include <string>
#include <vector>

#include "Stranded.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> args;
	for (int i = 1; i < argc; ++i)
	{
		args.push_back(std::string(argv[i]));
	}

	Stranded game;
	if (game.init(args))
	{
		game.run();
	}

	return 0;
}
