INCLUDES=-I. -I../../user_libs/SerialDebug/
LIBS=-lcppunit
SUBJECTS=../PaperBot.cpp ../PaperBotMove.cpp

all: unitTests
	./unitTests

unitTests: clean
	g++ --std=c++14 -g -o unitTests *.cpp $(SUBJECTS) $(INCLUDES) $(LIBS)
	
clean:
	rm -f *.o

