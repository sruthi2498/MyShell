CFLAGS=-std=gnu99
all :arrow stack edit alias command simple_command helper_to_parser lex_config yacc_config main
arrow : arrow.c arrow.h all_include.h
	gcc -g $(CFLAGS) -c arrow.c -o arrow.o -w
stack : stack.c stack.h all_include.h
	gcc -g $(CFLAGS) -c stack.c -o stack.o -w
edit : edit.c edit.h all_include.h
	gcc -g $(CFLAGS) -c edit.c -o edit.o -w
alias : alias_functions.c alias_functions.h all_include.h
	gcc -g $(CFLAGS) -c alias_functions.c -o alias_functions.o -w
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
	gcc -g $(CFLAGS) lex.yy.c y.tab.c -Wall main.c arrow.o stack.o edit.o alias_functions.o simple_command_functions.o command_functions.o helper_to_parser.o -ll -w -o main 
binaries= arrow stack edit alias simple_command command main
clean :
	rm -f $(binaries) *.o y.tab.c lex.yy.c y.tab.h 