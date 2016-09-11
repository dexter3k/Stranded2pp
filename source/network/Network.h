#pragma once

#include <memory>

class Modification;

class Network
{
public:
	Network();
	~Network();

	bool init(const Modification& modification);
};
