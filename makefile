simgrep: main.o	boyer_moore.o fileHandling.o inputHandling.o grep.o
	gcc -Wall -Wextra -Werror main.o boyer_moore.o fileHandling.o inputHandling.o grep.o -o simgrep

main.o:	main.c	boyer_moore.h inputHandling.h fileHandling.h grep.h
	gcc -Wall -Wextra -Werror -c main.c

boyer_moore.o:	boyer_moore.c
	gcc -Wall -Wextra -Werror -c boyer_moore.c

fileHandling.o: fileHandling.c
	gcc -Wall -Wextra -Werror -c fileHandling.c

inputHandling.o: inputHandling.c
	gcc -Wall -Wextra -Werror -c inputHandling.c

grep.o: grep.c
	gcc -Wall -Wextra -Werror -c grep.c
