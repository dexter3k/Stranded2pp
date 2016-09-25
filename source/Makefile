# Makefile for Stranded2pp

Target = stranded2pp
TargetPath = ../build/

SFMLDeps = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-network

LinuxLinkerFlags = -lGL
MacLinkerFlags = -framework OpenGL

CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++14 -I./
LDFLAGS = $(SFMLDeps) -lpthread

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS += $(LinuxLinkerFlags)
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += $(MacLinkerFlags)
endif

MAIN_OBJECTS = main.o \
	Stranded.o \
	Camera.o \
	Color.o \
	Device.o \
	Engine.o \
	FileSystem.o \
	Graphics.o \
	Gui.o \
	Image.o \
	Input.o \
	IntroScreen.o \
	Keyboard.o \
	MainMenuScreen.o \
	Material.o \
	Matrix4.o \
	Mesh.o \
	MeshBuffer.o \
	MeshNode.o \
	Modification.o \
	Mouse.o \
	Network.o \
	Node.o \
	OpenGLDevice.o \
	RawInputHandler.o \
	RingBuffer.o \
	Scene.o \
	Screen.o \
	Skybox.o \
	Sound.o \
	Texture.o \
	Vertex3D.o \
	Timer.o \
	Window.o

all: debug

debug: CXXFLAGS += -O0 -g
debug: stranded2

release: CXXFLAGS += -O2
release: stranded2

stranded2: $(MAIN_OBJECTS)
	$(CXX) $(MAIN_OBJECTS) -o $(TargetPath)$(Target) $(LDFLAGS)

main.o: main.cpp \
		Stranded.h \
		input/RawInputHandler.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Stranded.o: Stranded.cpp Stranded.h \
		common/Modification.h \
		common/Timer.h \
		engine/Engine.h \
		graphics/Graphics.h \
		input/Input.h \
		input/Keyboard.h \
		input/Mouse.h \
		input/RawInputHandler.h \
		network/Network.h \
		sound/Sound.h \
		window/Window.h
	$(CXX) $(CXXFLAGS) -c Stranded.cpp

Camera.o: graphics/scene/Camera.cpp graphics/scene/Camera.h \
		common/math/MathUtility.h \
		common/math/Matrix4.h \
		common/math/Rect.h \
		common/math/Vector2.h \
		common/math/Vector3.h \
		graphics/device/Device.h \
		graphics/scene/Node.h \
		graphics/scene/Scene.h \
		graphics/Color.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/Camera.cpp

Color.o: graphics/Color.cpp graphics/Color.h
	$(CXX) $(CXXFLAGS) -c graphics/Color.cpp

Device.o: graphics/device/Device.cpp graphics/device/Device.h \
		common/math/MathUtility.h \
		common/math/Matrix4.h \
		common/math/Rect.h \
		common/math/Vector2.h \
		common/math/Vector3.h \
		graphics/Color.h
	$(CXX) $(CXXFLAGS) -c graphics/device/Device.cpp

Engine.o: engine/Engine.cpp engine/Engine.h \
		common/Modification.h
	$(CXX) $(CXXFLAGS) -c engine/Engine.cpp

FileSystem.o: common/FileSystem.cpp common/FileSystem.h \
		common/RingBuffer.h
	$(CXX) $(CXXFLAGS) -c common/FileSystem.cpp

Graphics.o: graphics/Graphics.cpp graphics/Graphics.h \
		graphics/device/Device.h \
		graphics/device/OpenGLDevice.h \
		graphics/scene/Scene.h \
		input/Input.h \
		input/Keyboard.h \
		input/Mouse.h
	$(CXX) $(CXXFLAGS) -c graphics/Graphics.cpp

Gui.o: graphics/gui/Gui.cpp graphics/gui/Gui.h \
		graphics/gui/screen/Screen.h \
		graphics/gui/screen/IntroScreen.h \
		input/Input.h \
		input/Keyboard.h \
		input/Mouse.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/Gui.cpp

Image.o: graphics/Image.cpp graphics/Image.h
	$(CXX) $(CXXFLAGS) -c graphics/Image.cpp

Input.o: input/Input.cpp input/Input.h \
		input/Keyboard.h \
		input/Mouse.h \
		window/Window.h
	$(CXX) $(CXXFLAGS) -c input/Input.cpp

IntroScreen.o: graphics/gui/screen/IntroScreen.cpp \
	graphics/gui/screen/IntroScreen.h \
		graphics/gui/Gui.h \
		graphics/gui/screen/Screen.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/screen/IntroScreen.cpp

Keyboard.o: input/Keyboard.cpp input/Keyboard.h
	$(CXX) $(CXXFLAGS) -c input/Keyboard.cpp

MainMenuScreen.o: graphics/gui/screen/MainMenuScreen.cpp \
	graphics/gui/screen/MainMenuScreen.h \
		graphics/gui/Gui.h \
		graphics/gui/screen/Screen.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/screen/MainMenuScreen.cpp

Material.o: graphics/Material.cpp graphics/Material.h
	$(CXX) $(CXXFLAGS) -c graphics/Material.cpp

Matrix4.o: common/math/Matrix4.cpp common/math/Matrix4.h
	$(CXX) $(CXXFLAGS) -c common/math/Matrix4.cpp

Mesh.o: graphics/scene/Mesh.cpp graphics/scene/Mesh.h \
		graphics/scene/MeshBuffer.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/Mesh.cpp

MeshBuffer.o: graphics/scene/MeshBuffer.cpp graphics/scene/MeshBuffer.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/MeshBuffer.cpp

MeshNode.o: graphics/scene/MeshNode.cpp graphics/scene/MeshNode.h \
		graphics/scene/Mesh.h \
		graphics/scene/Node.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/MeshNode.cpp

Modification.o: common/Modification.cpp common/Modification.h \
		common/FileSystem.h
	$(CXX) $(CXXFLAGS) -c common/Modification.cpp

Mouse.o: input/Mouse.cpp input/Mouse.h
	$(CXX) $(CXXFLAGS) -c input/Mouse.cpp

Network.o: network/Network.cpp network/Network.h
	$(CXX) $(CXXFLAGS) -c network/Network.cpp

Node.o: graphics/scene/Node.cpp graphics/scene/Node.h \
		common/math/Vector3.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/Node.cpp

OpenGLDevice.o: graphics/device/OpenGLDevice.cpp graphics/device/OpenGLDevice.h
	$(CXX) $(CXXFLAGS) -c graphics/device/OpenGLDevice.cpp

RawInputHandler.o: input/RawInputHandler.cpp input/RawInputHandler.h
	$(CXX) $(CXXFLAGS) -c input/RawInputHandler.cpp

RingBuffer.o: common/RingBuffer.cpp common/RingBuffer.h
	$(CXX) $(CXXFLAGS) -c common/RingBuffer.cpp

Scene.o: graphics/scene/Scene.cpp graphics/scene/Scene.h \
		graphics/Graphics.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/Scene.cpp

Screen.o: graphics/gui/screen/Screen.cpp graphics/gui/screen/Screen.h \
		graphics/gui/Gui.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/screen/Screen.cpp
Skybox.o: graphics/scene/Skybox.cpp graphics/scene/Skybox.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/Skybox.cpp

Sound.o: sound/Sound.cpp sound/Sound.h
	$(CXX) $(CXXFLAGS) -c sound/Sound.cpp

Texture.o: graphics/Texture.cpp graphics/Texture.h
	$(CXX) $(CXXFLAGS) -c graphics/Texture.cpp

Vertex3D.o: graphics/Vertex3D.cpp graphics/Vertex3D.h \
		common/math/Vector2.h \
		common/math/Vector3.h \
		graphics/Color.h
	$(CXX) $(CXXFLAGS) -c graphics/Vertex3D.cpp

Timer.o: common/Timer.cpp common/Timer.h
	$(CXX) $(CXXFLAGS) -c common/Timer.cpp

Window.o: window/Window.cpp window/Window.h \
		common/Modification.h \
		input/Input.h
	$(CXX) $(CXXFLAGS) -c window/Window.cpp

clean:
	rm -r *.o

.PHONY: all debug release clean
