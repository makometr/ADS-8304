
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Werror

all:
	$(CXX) $(CXXFLAGS) Source/*.cpp -o lab4 