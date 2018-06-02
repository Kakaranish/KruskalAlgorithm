CPP_FLAGS=-std=c++11

all: utility.o graph.o
	g++ $(CPP_FLAGS) Utility.o Graph.o main.cpp -o output
	rm -f *.o
	./output

graph.o:
	g++ $(CPP_FLAGS) -c Graph.cpp

utility.o:
	g++ $(CPP_FLAGS) -c Utility.cpp 

clean:
	rm -f *.o