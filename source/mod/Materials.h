#pragma once

#include <string>

namespace mod
{

namespace Material
{

enum Type: int
{
	None,
	Wood,
	Stone,
	Dirt,
	Dust,
	Leaf,
	Metal,
	Flesh,
	Water,
	Lava,
	Fruit,
	Glass
};

bool canSwim(Type material);

bool isFireResistant(Type material);

unsigned getHardness(Type material);

Type fromString(std::string const & material);

} // namespace Material

} // namespace mod
