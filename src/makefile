simgrep:	main.o	boyer_moore.o
	gcc -Wall -Wextra -Werror main.o boyer_moore.o -o simgrep

main.o:	main.c	boyer_moore.h
	gcc -Wall -Wextra -Werror -c main.c

boyer_moore.o:	boyer_moore.c
	gcc -Wall -Wextra -Werror -c boyer_moore.c
