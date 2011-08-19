all: unitTests
	./unitTests

unitTests: clean
	g++ -g -o unitTests -lcppunit *.cpp
	
clean:
	rm -f *.o
