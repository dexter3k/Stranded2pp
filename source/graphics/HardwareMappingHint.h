#pragma once

namespace gfx
{

enum HardwareMappingHint
{
	// Don't store on the hardware
	HardwareMappingNever,

	// Rarely changed, usually stored completely on the hardware
	HardwareMappingStatic,

	// Sometimes changed, driver optimized placement
	HardwareMappingDynamic,

	// Always changed, cache optimizing on the GPU
	HardwareMappingStream
};

} // namespace gfx
