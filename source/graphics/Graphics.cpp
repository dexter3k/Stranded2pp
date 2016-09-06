#include "Graphics.h"

#include "common/Modification.h"
#include "input/Input.h"

Graphics::Graphics(const std::shared_ptr<Input>& input) :
	input(input)
{}

Graphics::~Graphics()
{}

bool Graphics::init(const std::shared_ptr<const Modification>& modification)
{
	return true;
}

void Graphics::update(float deltaTime)
{
	
}
