CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++11 
SOURCES = $(wildcard ./src/*.cpp)
OBJECTS = $(patsubst ./src/%.cpp,./build/%.o,$(SOURCES))
BIN = ./build/prog

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

./build/%.o : ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
	
clean:
	rm -rf $(OBJECTS) $(BIN)

	

