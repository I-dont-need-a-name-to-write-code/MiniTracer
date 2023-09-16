CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++11 
SOURCES = $(wildcard ./src/*.cpp)
OBJECTS = $(patsubst ./src/%.cpp,./build/%.o,$(SOURCES))
BIN = ./bin/prog
RENDER = ./render/image.ppm

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

./build/%.o : ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

run:
	$(BIN)

clean:
	rm -rf $(OBJECTS) $(BIN) $(RENDER)

