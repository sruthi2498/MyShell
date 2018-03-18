CFLAGS=-std=gnu99
all : lex_config yacc_config command simple_command main
command : command_functions.c command_functions.h all_include.h
	gcc -g $(CFLAGS) -c command_functions.c -o command_functions.o -w
simple_command : simple_command_functions.c simple_command_functions.h all_include.h
	gcc -g $(CFLAGS) -c simple_command_functions.c -o simple_command_functions.o -w
lex_config : shell.l
		lex shell.l
yacc_config : shell.y
	yacc -d shell.y
main : main.c all_include.h
	gcc -g $(CFLAGS) lex.yy.c y.tab.c -o main -Wall main.c simple_command_functions.o command_functions.o -ll -w
binaries= simple_command command main
clean:
	rm -f $(binaries) *.o