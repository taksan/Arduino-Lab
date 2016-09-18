all: paperMove

clean:
	rm -f *.o

paperMove: ../PaperBotMove.cpp ../PaperBot.cpp PaperBotMoveSpike.cpp
	g++ -g -c ../PaperBotMove.cpp ../PaperBot.cpp Arduino.cpp PaperBotMoveSpike.cpp -I. -I../../user_libs/SerialDebug
	g++ -g -o paperMoveTest *.o
