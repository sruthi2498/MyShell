CFLAGS=-std=gnu99
all :arrow stack command simple_command helper_to_parser lex_config yacc_config main
arrow : arrow.c arrow.h all_include.h
	gcc -g $(CFLAGS) -c arrow.c -o arrow.o -w
stack : stack.c stack.h all_include.h
	gcc -g $(CFLAGS) -c stack.c -o stack.o -w
command : command_functions.c command_functions.h all_include.h
	gcc -g $(CFLAGS) -c command_functions.c -o command_functions.o -w
simple_command : simple_command_functions.c simple_command_functions.h all_include.h
	gcc -g $(CFLAGS) -c simple_command_functions.c -o simple_command_functions.o -w
helper_to_parser : helper_to_parser.c helper_to_parser.h all_include.h
	gcc -g $(CFLAGS) -c helper_to_parser.c simple_command_functions.o command_functions.o -w -o helper_to_parser.o 
lex_config : shell.l
		lex shell.l
yacc_config : shell.y
	yacc -d shell.y
main : main.c all_include.h
	gcc -g $(CFLAGS) lex.yy.c y.tab.c -Wall main.c arrow.o stack.o simple_command_functions.o command_functions.o helper_to_parser.o -ll -w -o main 
binaries= arrow stack simple_command command main
clean :
	rm -f $(binaries) *.o