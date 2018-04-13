simgrep: main.o	fileHandling.o inputHandling.o grep.o lineHandling.o
	gcc -Wall -Wextra main.o fileHandling.o inputHandling.o grep.o lineHandling.o -o simgrep

main.o:	main.c	inputHandling.h fileHandling.h grep.h
	gcc -Wall -Wextra -c main.c

fileHandling.o: fileHandling.c	fileHandling.h	lineHandling.h
	gcc -Wall -Wextra -c fileHandling.c

inputHandling.o: inputHandling.c	inputHandling.h
	gcc -Wall -Wextra -c inputHandling.c

grep.o: grep.c	grep.h
	gcc -Wall -Wextra -c grep.c

lineHandling.o:	lineHandling.c	lineHandling.h
	gcc -Wall -Wextra -c lineHandling.c
