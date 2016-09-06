#pragma once

#include <memory>

class Input;
class Modification;

class Graphics
{
public:
	Graphics(const std::shared_ptr<Input>& input);
	~Graphics();

	bool init(const std::shared_ptr<const Modification>& modification);
	void update(float deltaTime);
private:
	std::shared_ptr<Input>	input;
};
