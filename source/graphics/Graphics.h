#pragma once

#include <memory>

class Input;

class Graphics
{
public:
	Graphics(const std::shared_ptr<Input>& input);
	~Graphics();

	bool init();
	void update(float deltaTime);
private:
	std::shared_ptr<Input>	input;
};
