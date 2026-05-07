CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wpedantic -Wconversion

all: test

clean:
	rm test

test: Linear.hpp Tree.hpp HashMap.hpp
	$(CXX) $(CXXFLAGS) test.cpp -o test
