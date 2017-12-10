#pragma once

#include <array>
#include <string>

#include "graphics/Color.h"

namespace mod
{

std::array<gfx::Color, 24> loadLightcycle(std::string const & modPath);

} // namespace mod
