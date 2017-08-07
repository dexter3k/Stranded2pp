#! /bin/bash
set -e

if [ -f build/stranded2pp ];
then
	cd build

	valgrind --leak-check=full ./stranded2pp -win
fi
