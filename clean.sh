#! /bin/bash

if [ -f source/Makefile ];
then
	cd source

	make clean

	cd ..
fi
