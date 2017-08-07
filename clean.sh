#! /bin/bash

if [ -d build ];
then
	cd build

	# Remove common CMake data
	rm -rf CMakeFiles
	rm -f cmake_install.cmake
	rm -f CMakeCache.txt
	rm -f Makefile
fi
