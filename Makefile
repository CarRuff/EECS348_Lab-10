CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: calc

calc: main.o calculator.o
	$(CXX) $(CXXFLAGS) -o calc main.o calculator.o

main.o: main.cpp calculator.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	$(CXX) $(CXXFLAGS) -c calculator.cpp

clean:
	rm -f *.o calc
