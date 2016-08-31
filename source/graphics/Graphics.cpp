#include "Graphics.h"

#include "input/Input.h"

Graphics::Graphics(const std::shared_ptr<Input>& input) :
	input(input)
{}

Graphics::~Graphics()
{}

bool Graphics::init()
{
	return true;
}
