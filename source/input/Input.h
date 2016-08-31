#pragma once

#include <memory>

class Window;

class Input
{
public:
	Input(const std::shared_ptr<Window>& window);
	~Input();

	bool init();
private:
	std::shared_ptr<Window>	window;
};
