
Ruzzle_Solver.exe: src/main.c fonct.o
	gcc src/main.c fonct.o -o bin/Ruzzle_Solver.exe -g -Wall
	rm fonct.o

fonct.o: src/fonct.c
	gcc src/fonct.c -o fonct.o -g -Wall

