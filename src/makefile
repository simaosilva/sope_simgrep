simgrep: main.o	boyer_moore.o fileHandling.o inputHandling.o grep.o
	gcc -Wall -Wextra main.o boyer_moore.o fileHandling.o inputHandling.o grep.o -o simgrep

main.o:	main.c	boyer_moore.h inputHandling.h fileHandling.h grep.h
	gcc -Wall -Wextra -c main.c

boyer_moore.o:	boyer_moore.c
	gcc -Wall -Wextra -c boyer_moore.c

fileHandling.o: fileHandling.c
	gcc -Wall -Wextra -c fileHandling.c

inputHandling.o: inputHandling.c
	gcc -Wall -Wextra -c inputHandling.c

grep.o: grep.c
	gcc -Wall -Wextra -c grep.c
