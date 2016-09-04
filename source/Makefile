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
	Engine.o \
	FileSystem.o \
	Graphics.o \
	Gui.o \
	Input.o \
	Keyboard.o \
	Modification.o \
	Mouse.o \
	Network.o \
	RingBuffer.o \
	Sound.o \
	Window.o

all: debug

debug: CXXFLAGS += -O0 -g
debug: stranded2

release: CXXFLAGS += -O2
release: stranded2

stranded2: $(MAIN_OBJECTS)
	$(CXX) $(MAIN_OBJECTS) -o $(TargetPath)$(Target) $(LDFLAGS)

main.o: main.cpp \
		Stranded.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Stranded.o: Stranded.cpp Stranded.h \
		common/FileSystem.h \
		common/Modification.h \
		engine/Engine.h \
		graphics/Graphics.h \
		gui/Gui.h \
		input/Input.h \
		network/Network.h \
		sound/Sound.h \
		window/Window.h
	$(CXX) $(CXXFLAGS) -c Stranded.cpp

Engine.o: engine/Engine.cpp engine/Engine.h \
		graphics/Graphics.h \
		gui/Gui.h \
		input/Input.h \
		input/Keyboard.h \
		input/Mouse.h \
		network/Network.h \
		sound/Sound.h
	$(CXX) $(CXXFLAGS) -c engine/Engine.cpp

FileSystem.o: common/FileSystem.cpp common/FileSystem.h
	$(CXX) $(CXXFLAGS) -c common/FileSystem.cpp

Graphics.o: graphics/Graphics.cpp graphics/Graphics.h \
		input/Input.h \
		input/Keyboard.h \
		input/Mouse.h
	$(CXX) $(CXXFLAGS) -c graphics/Graphics.cpp

Gui.o: gui/Gui.cpp gui/Gui.h \
		input/Input.h \
		input/Keyboard.h \
		input/Mouse.h
	$(CXX) $(CXXFLAGS) -c gui/Gui.cpp

Input.o: input/Input.cpp input/Input.h \
		input/Keyboard.h \
		input/Mouse.h \
		window/Window.h
	$(CXX) $(CXXFLAGS) -c input/Input.cpp

Keyboard.o: input/Keyboard.cpp input/Keyboard.h
	$(CXX) $(CXXFLAGS) -c input/Keyboard.cpp

Modification.o: common/Modification.cpp common/Modification.h \
		common/FileSystem.h
	$(CXX) $(CXXFLAGS) -c common/Modification.cpp

Mouse.o: input/Mouse.cpp input/Mouse.h
	$(CXX) $(CXXFLAGS) -c input/Mouse.cpp

Network.o: network/Network.cpp network/Network.h
	$(CXX) $(CXXFLAGS) -c network/Network.cpp

RingBuffer.o: common/RingBuffer.cpp common/RingBuffer.h
	$(CXX) $(CXXFLAGS) -c common/RingBuffer.cpp

Sound.o: sound/Sound.cpp sound/Sound.h
	$(CXX) $(CXXFLAGS) -c sound/Sound.cpp

Window.o: window/Window.cpp window/Window.h \
		common/Modification.h
	$(CXX) $(CXXFLAGS) -c window/Window.cpp

clean:
	rm -r *.o

.PHONY: all debug release clean
