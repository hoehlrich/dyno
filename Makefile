# THE NAME OF YOUR EXECUTABLE
TARGET = dyno
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp App.hpp DataCollector.hpp Rotation.hpp

# NO EDITS NEEDED BELOW THIS LINE
CXX = g++
CXXFLAGS = -O2
CXXFLAGS_DEBUG = -g
CXXFLAGS_WARN = -Wall -Wextra -Wunreachable-code -Wshadow -Wpedantic
CPPVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	DEL = del
	Q =

	INC_PATH = Z:/CSCI200/include/
	LIB_PATH = Z:/CSCI200/lib/

	RPATH =
else
	DEL = rm -f
	Q = "

	INC_PATHS = -I/usr/local/include/
	LIB_PATHS = -L/usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
		RPATH = -Wl,-rpath /usr/local/lib
	endif
	ifeq ($(UNAME_S),Darwin)
		CXXFLAGS += -D OSX
		RPATH = -Wl,-rpath,/Library/Frameworks
	endif

	UNAME_P := $(shell uname -p)
endif

LIBS = -lftd2xx -lpthread -lrt -lboost_thread

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(RPATH) $(LIB_PATHS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CPPVERSION) $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARN) -o $@ -c $< $(INC_PATHS)

clean:
	$(DEL) $(TARGET) $(OBJECTS)
	
depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp App.hpp DataCollector.hpp Rotation.hpp
