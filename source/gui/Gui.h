#pragma once

#include <memory>

class Input;

class Gui
{
public:
	Gui(const std::shared_ptr<Input>& input);
	~Gui();

	bool init();
private:
	std::shared_ptr<Input> input;
};
