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
	Cfg.o \
	Engine.o \
	FileSystem.o \
	Graphics.o \
	Gui.o \
	Input.o \
	Modification.o \
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

Cfg.o: common/Cfg.cpp common/Cfg.h \
		common/RingBuffer.h
	$(CXX) $(CXXFLAGS) -c common/Cfg.cpp

Engine.o: engine/Engine.cpp engine/Engine.h \
		graphics/Graphics.h \
		gui/Gui.h \
		input/Input.h \
		network/Network.h \
		sound/Sound.h
	$(CXX) $(CXXFLAGS) -c engine/Engine.cpp

FileSystem.o: common/FileSystem.cpp common/FileSystem.h
	$(CXX) $(CXXFLAGS) -c common/FileSystem.cpp

Graphics.o: graphics/Graphics.cpp graphics/Graphics.h \
		input/Input.h
	$(CXX) $(CXXFLAGS) -c graphics/Graphics.cpp

Gui.o: gui/Gui.cpp gui/Gui.h \
		input/Input.h
	$(CXX) $(CXXFLAGS) -c gui/Gui.cpp

Input.o: input/Input.cpp input/Input.h \
		window/Window.h
	$(CXX) $(CXXFLAGS) -c input/Input.cpp

Modification.o: common/Modification.cpp common/Modification.h \
		common/Cfg.h \
		common/FileSystem.h
	$(CXX) $(CXXFLAGS) -c common/Modification.cpp

Network.o: network/Network.cpp network/Network.h
	$(CXX) $(CXXFLAGS) -c network/Network.cpp

RingBuffer.o: common/RingBuffer.cpp common/RingBuffer.h
	$(CXX) $(CXXFLAGS) -c common/RingBuffer.cpp

Sound.o: sound/Sound.cpp sound/Sound.h
	$(CXX) $(CXXFLAGS) -c sound/Sound.cpp

Window.o: window/Window.cpp window/Window.h
	$(CXX) $(CXXFLAGS) -c window/Window.cpp

clean:
	rm -r *.o

.PHONY: all debug release clean
