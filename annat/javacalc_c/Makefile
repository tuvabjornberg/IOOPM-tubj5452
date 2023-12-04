
ast: ast.c
	gcc -Wall -Wextra -Wpedantic -g ast.c -o ast

memtest: ast
	valgrind --leak-check=full ./ast

clean: 
	rm -f ast