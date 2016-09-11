#pragma once

#include <memory>

class Modification;

class Sound
{
public:
	Sound();
	~Sound();

	bool init(const Modification& modification);
};
