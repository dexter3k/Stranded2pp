#! /bin/bash

if [ -f build/stranded2pp ];
then
	cd build

	./stranded2pp -win

	cd ..
fi
