# Makefile for Stranded2pp

Target = stranded2pp
TargetPath = ../build/

SFMLDeps = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-network

LinuxLinkerFlags = -lGL
MacLinkerFlags = -framework OpenGL

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++14 -I./
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
	Compiler.o \
	CompilerUtils.o \
	Device.o \
	Engine.o \
	ExecutionContext.o \
	FileSystem.o \
	Frustum.o \
	Graphics.o \
	Gui.o \
	GuiBackgroundImage.o \
	GuiButton.o \
	GuiElement.o \
	GuiImage.o \
	Image.o \
	Input.o \
	IndexBuffer.o \
	InfinitePlane.o \
	IntroScreen.o \
	Keyboard.o \
	Line.o \
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
	ParseUtils.o \
	Plane.o \
	Program.o \
	RawInputHandler.o \
	RingBuffer.o \
	SaveGameUtils.o \
	Scene.o \
	Screen.o \
	Skybox.o \
	Sound.o \
	StringUtils.o \
	Terrain.o \
	Texture.o \
	Timer.o \
	Token.o \
	Vertex3D.o \
	VertexBuffer.o \
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
		engine/script/ExecutionContext.h \
		engine/script/Program.h \
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

Compiler.o: engine/script/Compiler.cpp engine/script/Compiler.h \
		engine/script/CompilerUtils.h \
		engine/script/Token.h
	$(CXX) $(CXXFLAGS) -c engine/script/Compiler.cpp

CompilerUtils.o: engine/script/CompilerUtils.cpp engine/script/CompilerUtils.h \
		engine/script/Token.h
	$(CXX) $(CXXFLAGS) -c engine/script/CompilerUtils.cpp

Device.o: graphics/device/Device.cpp graphics/device/Device.h \
		common/math/MathUtility.h \
		common/math/Matrix4.h \
		common/math/Rect.h \
		common/math/Vector2.h \
		common/math/Vector3.h \
		graphics/Color.h
	$(CXX) $(CXXFLAGS) -c graphics/device/Device.cpp

Engine.o: engine/Engine.cpp engine/Engine.h \
		common/Modification.h \
		engine/SaveGameUtils.h \
		engine/script/Compiler.h \
		engine/script/ExecutionContext.h \
		engine/script/Program.h
	$(CXX) $(CXXFLAGS) -c engine/Engine.cpp

ExecutionContext.o: engine/script/ExecutionContext.cpp \
	engine/script/ExecutionContext.h
	$(CXX) $(CXXFLAGS) -c engine/script/ExecutionContext.cpp

FileSystem.o: common/FileSystem.cpp common/FileSystem.h \
		common/RingBuffer.h
	$(CXX) $(CXXFLAGS) -c common/FileSystem.cpp

Frustum.o: common/math/Frustum.cpp common/math/Frustum.h \
		common/math/Matrix4.h \
		common/math/Plane.h \
		common/math/Vector3.h
	$(CXX) $(CXXFLAGS) -c common/math/Frustum.cpp

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
		graphics/gui/screen/MainMenuScreen.h \
		input/Input.h \
		input/Keyboard.h \
		input/Mouse.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/Gui.cpp

GuiBackgroundImage.o: graphics/gui/GuiBackgroundImage.cpp \
	graphics/gui/GuiBackgroundImage.h \
		graphics/device/Device.h \
		graphics/gui/Gui.h \
		graphics/gui/GuiElement.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/GuiBackgroundImage.cpp

GuiButton.o: graphics/gui/GuiButton.cpp graphics/gui/GuiButton.h \
		graphics/device/Device.h \
		graphics/gui/Gui.h \
		graphics/gui/GuiElement.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/GuiButton.cpp

GuiElement.o: graphics/gui/GuiElement.cpp graphics/gui/GuiElement.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/GuiElement.cpp

GuiImage.o: graphics/gui/GuiImage.cpp graphics/gui/GuiImage.h \
		graphics/device/Device.h \
		graphics/gui/Gui.h \
		graphics/gui/GuiElement.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/GuiImage.cpp

Image.o: graphics/Image.cpp graphics/Image.h
	$(CXX) $(CXXFLAGS) -c graphics/Image.cpp

Input.o: input/Input.cpp input/Input.h \
		input/Keyboard.h \
		input/Mouse.h \
		window/Window.h
	$(CXX) $(CXXFLAGS) -c input/Input.cpp

IndexBuffer.o: graphics/IndexBuffer.cpp graphics/IndexBuffer.h \
		graphics/IndexSize.h
	$(CXX) $(CXXFLAGS) -c graphics/IndexBuffer.cpp

InfinitePlane.o: graphics/scene/InfinitePlane.cpp \
	graphics/scene/InfinitePlane.h \
		graphics/scene/Node.h \
		graphics/Material.h \
		graphics/Vertex3D.h \
		graphics/scene/Camera.h \
		graphics/device/Device.h \
		graphics/scene/Scene.h \
		graphics/IndexSize.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/InfinitePlane.cpp

IntroScreen.o: graphics/gui/screen/IntroScreen.cpp \
	graphics/gui/screen/IntroScreen.h \
		graphics/gui/Gui.h \
		graphics/gui/screen/Screen.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/screen/IntroScreen.cpp

Keyboard.o: input/Keyboard.cpp input/Keyboard.h
	$(CXX) $(CXXFLAGS) -c input/Keyboard.cpp

Line.o: common/math/Line.cpp common/math/Line.h \
		common/math/Vector3.h
	$(CXX) $(CXXFLAGS) -c common/math/Line.cpp

MainMenuScreen.o: graphics/gui/screen/MainMenuScreen.cpp \
	graphics/gui/screen/MainMenuScreen.h \
		graphics/gui/Gui.h \
		graphics/gui/screen/Screen.h
	$(CXX) $(CXXFLAGS) -c graphics/gui/screen/MainMenuScreen.cpp

Material.o: graphics/Material.cpp graphics/Material.h
	$(CXX) $(CXXFLAGS) -c graphics/Material.cpp

Matrix4.o: common/math/Matrix4.cpp common/math/Matrix4.h
	$(CXX) $(CXXFLAGS) -c common/math/Matrix4.cpp

Mesh.o: graphics/Mesh.cpp graphics/Mesh.h \
		graphics/MeshBuffer.h
	$(CXX) $(CXXFLAGS) -c graphics/Mesh.cpp

MeshBuffer.o: graphics/MeshBuffer.cpp graphics/MeshBuffer.h
	$(CXX) $(CXXFLAGS) -c graphics/MeshBuffer.cpp

MeshNode.o: graphics/scene/MeshNode.cpp graphics/scene/MeshNode.h \
		graphics/scene/Node.h \
		graphics/Mesh.h
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

ParseUtils.o: common/ParseUtils.cpp common/ParseUtils.h
	$(CXX) $(CXXFLAGS) -c common/ParseUtils.cpp

Plane.o: common/math/Plane.cpp common/math/Plane.h \
		common/math/MathUtility.h \
		common/math/Vector3.h \
		common/math/Line.h
	$(CXX) $(CXXFLAGS) -c common/math/Plane.cpp

Program.o: engine/script/Program.cpp engine/script/Program.h \
		engine/script/ExecutionContext.h \
		engine/script/Token.h
	$(CXX) $(CXXFLAGS) -c engine/script/Program.cpp

RawInputHandler.o: input/RawInputHandler.cpp input/RawInputHandler.h
	$(CXX) $(CXXFLAGS) -c input/RawInputHandler.cpp

RingBuffer.o: common/RingBuffer.cpp common/RingBuffer.h
	$(CXX) $(CXXFLAGS) -c common/RingBuffer.cpp

SaveGameUtils.o: engine/SaveGameUtils.cpp engine/SaveGameUtils.h \
		engine/Engine.h \
		common/FileSystem.h \
		common/RingBuffer.h \
		common/math/Vector2.h \
		common/math/Vector3.h \
		graphics/Image.h \
		graphics/Color.h
	$(CXX) $(CXXFLAGS) -c engine/SaveGameUtils.cpp

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

StringUtils.o: common/StringUtils.cpp common/StringUtils.h
	$(CXX) $(CXXFLAGS) -c common/StringUtils.cpp

Terrain.o: graphics/scene/Terrain.cpp graphics/scene/Terrain.h \
		graphics/scene/Node.h
	$(CXX) $(CXXFLAGS) -c graphics/scene/Terrain.cpp

Texture.o: graphics/Texture.cpp graphics/Texture.h
	$(CXX) $(CXXFLAGS) -c graphics/Texture.cpp

Timer.o: common/Timer.cpp common/Timer.h
	$(CXX) $(CXXFLAGS) -c common/Timer.cpp

Token.o: engine/script/Token.cpp engine/script/Token.h
	$(CXX) $(CXXFLAGS) -c engine/script/Token.cpp

Vertex3D.o: graphics/Vertex3D.cpp graphics/Vertex3D.h \
		common/math/Vector2.h \
		common/math/Vector3.h \
		graphics/Color.h
	$(CXX) $(CXXFLAGS) -c graphics/Vertex3D.cpp

VertexBuffer.o: graphics/VertexBuffer.cpp graphics/VertexBuffer.h \
		graphics/Vertex3D.h
	$(CXX) $(CXXFLAGS) -c graphics/VertexBuffer.cpp

Window.o: window/Window.cpp window/Window.h \
		common/Modification.h \
		input/Input.h
	$(CXX) $(CXXFLAGS) -c window/Window.cpp

clean:
	rm -r *.o

.PHONY: all debug release clean
