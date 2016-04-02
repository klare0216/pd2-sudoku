readIn:readIn.o Sudoku.o
	g++ -o readIn readIn.o Sudoku.o

readIn.o:readIn.cpp Sudoku.h
	g++ -c readIn.cpp

Sudoku.o:Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp

