cmake_minimum_required(VERSION 3.20)

# C++ Settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -pedantic")
if (APPLE)
	# First flag fixes this:
	# 	Definition of implicit copy assignment operator for 'Program' is deprecated because it has a user-declared copy constructor
	# 	at: source/engine/script/Program.h, line 13.
	# Second one removes OpenGL warnings
	# Other two are used to fix:
	#	arithmetic on a null pointer treated as a cast from integer to pointer is a GNU extension
	#	at: source/graphics/device/OpenGLDevice.cpp, line 25.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-copy -Wno-deprecated-declarations -Wno-gnu -Wno-null-pointer-arithmetic")
endif()

project(Stranded2pp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SFML 2.4 REQUIRED COMPONENTS system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

include_directories(source)

file(GLOB_RECURSE SOURCES source/*.cpp)


if (APPLE)
	# First is for this:
	# Definition of implicit copy assignment operator for 'Program' is deprecated because it has a user-declared copy constructor
	# at: source/engine/script/Program.h, line 13.
	# Second one removes OpenGL warnings
	add_definitions(-Wno-deprecated-copy -Wno-deprecated-declarations -Wno-gnu -Wno-null-pointer-arithmetic)
endif()

add_executable(stranded2pp ${SOURCES})

target_link_libraries(stranded2pp
	${OPENGL_gl_LIBRARY}
	${SFML_LIBRARIES}
)
