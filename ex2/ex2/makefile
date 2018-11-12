a.out: Board.o GameFlow.o Player.o Cell.o main.o
	g++ Board.o GameFlow.o Player.o Cell.o main.o
main.o: main.cpp GameFlow.h
	g++ -c main.cpp
Board.o: Board.cpp Board.h
	g++ -c Board.cpp
Player.o: Player.cpp Player.h
	g++ -c Player.cpp
Cell.o: Cell.cpp Cell.h
	g++ -c Cell.cpp
GameFlow.o: GameFlow.cpp GameFlow.h
	g++ -c GameFlow.cpp
clean:
	rm -f *.o a.out
kill:
	rm -f *.h *.cpp makefile a.out
