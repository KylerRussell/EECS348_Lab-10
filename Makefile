CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: calculator

calculator: main.o calculator.o
	$(CXX) $(CXXFLAGS) -o calculator.exe main.o calculator.o

main.o: main.cpp calculator.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	$(CXX) $(CXXFLAGS) -c calculator.cpp

clean:
	rm -f calculator.exe *.o

test: all
	cmake -S . -B build
	cmake --build build
	cd build/tests && ctest --output-on-failure


