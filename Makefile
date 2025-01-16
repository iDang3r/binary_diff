
TARGET := ar_diff
SOURCES := $(wildcard src/*.cc)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.cc,%.o, $(SOURCES)))

INCLUDE := -Isrc
LIBPATH :=
LIBS :=

CXXFLAGS := -Wall -std=c++17
LINKFLAGS := 

CXX := g++

all: obj | $(OBJECTS)
	$(CXX) $(LINKFLAGS) $(INCLUDE) $(OBJECTS) -o $(TARGET) $(LIBPATH) $(LIBS)

%.o: ../src/%.cc
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@

obj:
	mkdir -p $@

.PHONY: clean

clean:
	rm -rf obj/*
	rm -f $(TARGET)
