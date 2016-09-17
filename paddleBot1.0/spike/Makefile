all: paperMove

clean:
	rm -f *.o

paperMove: ../PaperBotMove.cpp ../PaperBot.cpp PaperBotMoveSpike.cpp
	g++ -g -c ../PaperBotMove.cpp ../PaperBot.cpp PaperBotMoveSpike.cpp -I.
	g++ -g -o paperMoveTest *.o
