cmake_minimum_required(VERSION 2.6)

project(Stranded2pp)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(SFML 2.4 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

include_directories(source)

file(GLOB_RECURSE SOURCES source/*.cpp)

add_definitions(-std=c++14 -Wall -Wextra -Werror -pedantic)

add_executable(stranded2pp ${SOURCES})

target_link_libraries(stranded2pp
	${OPENGL_gl_LIBRARY}
	${SFML_LIBRARIES}
)
