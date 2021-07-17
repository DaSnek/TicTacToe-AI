all: game 

%: %.cpp
	g++ -std=c++17 -o $@ $^
