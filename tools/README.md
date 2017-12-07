# Tools

Some of the tools that are used in the development process.

## `dump_b3d.py`
This tool is useful for dumping some of the *.b3d files.
Usage:
```
./dump_b3d.py <model.b3d>
```

## `b3dpreview`
![screen shot 2017-12-07 at 19 39 19](https://user-images.githubusercontent.com/7492740/33729473-73062fca-db86-11e7-8358-1f8f8c7b6825.png)

This tool is for previewing Blitz3D models. Mostly used as a testbed for the graphics engine.
Compile:
```
g++ -std=c++14 -Wall -Wextra -Wpedantic -I../source/ ./b3dpreview.cpp ../source/common/ByteBuffer.cpp ../source/common/FileSystem.cpp ../source/common/RingBuffer.cpp -o b3dpreview -lsfml-system -lsfml-graphics -lsfml-window -lGL
```
Note: replace `-lGL` with `-framework OpenGL` on MacOS

Usage:
```
./b3dpreview <model.b3d>
```
