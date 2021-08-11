assembler: assembler.o secondPass.o files.o files.o firstPass.o list.o operations.o errorDataBase.o utility.o word.o checkData.o
	gcc -g -ansi -Wall -pedantic -Werror assembler.o secondPass.o files.o firstPass.o list.o operations.o errorDataBase.o utility.o word.o checkData.o -o assembler  -lm


assembler.o: assembler.c assembler.h
	gcc -c -g -ansi -Wall -pedantic -Werror assembler.c -o assembler.o

files.o: files.c assembler.h
	gcc -c -g -ansi -Wall -pedantic -Werror files.c -o files.o

firstPass.o: firstPass.c assembler.h firstPass.h 
	gcc -c -g -ansi -Wall -pedantic -Werror firstPass.c -o firstPass.o

list.o: list.c assembler.h 
	gcc -c -g -ansi -Wall -pedantic -Werror list.c -o list.o

operations.o: operation.c assembler.h 
	gcc -c -g -ansi -Wall -pedantic -Werror operation.c -o operations.o

errorDataBase.o: errorDataBase.c assembler.h
	gcc -c -g -ansi -Wall -pedantic -Werror errorDataBase.c -o errorDataBase.o

utility.o: utility.c assembler.h 
	gcc -c -g -ansi -Wall -pedantic -Werror utility.c -o utility.o -lm

word.o: word.c assembler.h 
	gcc -c -g -ansi -Wall -pedantic -Werror word.c -o word.o

secondPass.o: secondPass.c assembler.h secondPass.h
	gcc -c -g -ansi -Wall -pedantic -Werror secondPass.c -o secondPass.o 

checkData.o: checkData.c firstPass.h
	gcc -c -g -ansi -Wall -pedantic -Werror checkData.c -o checkData.o 

