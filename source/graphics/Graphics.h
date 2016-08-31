#pragma once

#include <memory>

class Input;

class Graphics
{
public:
	Graphics(const std::shared_ptr<Input>& input);
	~Graphics();

	bool init();
private:
	std::shared_ptr<Input>	input;
};
