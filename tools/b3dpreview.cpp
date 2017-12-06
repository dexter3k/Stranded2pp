#include <iostream>

#include <SFML/Graphics.hpp>

void printUsage(std::string const & filename)
{
	std::cout << "Usage:\n"
		<< "\t" << filename << " <model.b3d>" << std::endl;
}

int main(int argc, char * argv[])
{
	std::vector<std::string> const arguments(argv, argv + argc);
	if (arguments.size() < 2) {
		printUsage(arguments[0]);
		std::exit(1);
	}

	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 0;
	contextSettings.antialiasingLevel = 0;
	contextSettings.majorVersion = 2;
	contextSettings.minorVersion = 1;

	std::string title = ".b3d Preview: ";
	title += arguments[1];

	sf::RenderWindow window(
		sf::VideoMode(800, 600, 32), title, sf::Style::Default, contextSettings);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		window.display();
	}

	return 0;
}
