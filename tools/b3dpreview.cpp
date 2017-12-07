// Build me:
// g++ -std=c++14 -Wall -Wextra -Wpedantic -I../source/ ./b3dpreview.cpp ../source/common/ByteBuffer.cpp ../source/common/FileSystem.cpp ../source/common/RingBuffer.cpp -o b3dpreview -lsfml-system -lsfml-graphics -lsfml-window

#include <iostream>

#include <SFML/Graphics.hpp>

#include "common/FileSystem.h"
#include "common/ByteBuffer.h"

class Model
{
public:
	Model(std::string const & filename) {
		loadFromFile(filename);
	}

	void loadFromFile(std::string const & filename) {
		ByteBuffer buffer(fs::getFileSize(filename));
		if (!fs::loadFile(filename, buffer)) {
			std::exit(1);
		}
	}
};

void showModel(Model const &) {
	// sf::ContextSettings contextSettings;
	// contextSettings.depthBits = 24;
	// contextSettings.stencilBits = 0;
	// contextSettings.antialiasingLevel = 0;
	// contextSettings.majorVersion = 2;
	// contextSettings.minorVersion = 1;

	// std::string title = ".b3d Preview: ";
	// title += arguments[1];

	// sf::RenderWindow window(
	// 	sf::VideoMode(800, 600, 32), title, sf::Style::Default, contextSettings);

	// while (window.isOpen()) {
	// 	sf::Event event;
	// 	while (window.pollEvent(event)) {
	// 		if (event.type == sf::Event::Closed) {
	// 			window.close();
	// 		}
	// 	}

	// 	window.clear();

	// 	window.display();
	// }
}

void printUsage(std::string const & filename) {
	std::cout << "Usage:\n"
		<< "\t" << filename << " <model.b3d>" << std::endl;
}

int main(int argc, char * argv[]) {
	std::vector<std::string> const arguments(argv, argv + argc);
	if (arguments.size() < 2) {
		printUsage(arguments[0]);
		std::exit(1);
	}

	Model model(arguments[1]);
	showModel(model);

	return 0;
}
