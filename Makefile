
TARGET := ar_diff
SOURCES := $(wildcard src/*.cc)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.cc,%.o, $(SOURCES)))

INCLUDE := -Isrc
LIBPATH :=
LIBS :=

FLAGS := -O3
CXXFLAGS := $(FLAGS) -Wall -std=c++17
LINKFLAGS := $(FLAGS)

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
