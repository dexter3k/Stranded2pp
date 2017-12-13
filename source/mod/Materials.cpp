#include "Materials.h"

#include <stdexcept>

namespace mod
{

namespace Material
{

bool canSwim(Type material)
{
	switch (material) {
	case Wood:
	case Leaf:
		return true;
	default:
		return false;
	}
}

bool isFireResistant(Type material)
{
	switch (material) {
	case Stone:
	case Dirt:
	case Dust:
	case Metal:
	case Water:
	case Glass:
		return true;
	default:
		return false;
	}
}

unsigned getHardness(Type material)
{
	switch (material) {
	case None:
	case Wood:
	case Dirt:
	case Dust:
	case Flesh:
	case Fruit:
		return 1;
	case Stone:
	case Metal:
	case Glass:
		return 2;
	default:
		return 0;
	}
}

Type fromString(std::string const & material)
{
	if (material == "none") return None;
	if (material == "wood") return Wood;
	if (material == "stone") return Stone;
	if (material == "dirt") return Dirt;
	if (material == "dust") return Dust;
	if (material == "leaf") return Leaf;
	if (material == "metal") return Metal;
	if (material == "flesh") return Flesh;
	if (material == "water") return Water;
	if (material == "lava") return Lava;
	if (material == "fruit") return Fruit;
	if (material == "glass") return Glass;
	try {
		return static_cast<Type>(std::stoi(material));
	} catch (std::invalid_argument &) {
		return None;
	}
}

} // namespace Material

} // namespace mod
