complex: mycomp.o complex.o utility.o
	gcc -g -Wall -ansi -pedantic main.o complex.o utility.o -o complex -lm
utility.o:utility.c
	gcc -c -Wall -ansi -pedantic utility.c -o utility.o	
complex.o: complex.c
	gcc -c -Wall -ansi -pedantic complex.c -o complex.o -lm
mycomp.o: mycomp.c complex.h
	gcc -c -Wall -ansi -pedantic mycomp.c -o main.o


