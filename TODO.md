# Main project TODO list

## High priority
ASAP!

* Decide about Modification class and some resource manager
* Rewrite all the trash (more details, pls?)
* [Done] Screen system should be moved out of Gui to Stranded
* [Done] Move to CMake build system

## Medium priority
Just after High priority tasks

* Improve text rendering by drawing whole string in a single OpenGL call. Currently makes a call per character.
* Write COMPILING.md

## Low priority
Lower priority tasks

* Support all file formats that the original game supports. Currently `mp3` and some features of `png` are known to be unsupported
	* Add support for original `moon_a.png` and `flames0_a.png` sprites
	* Add support for mp3 files (or wait for SFML to do so?)
