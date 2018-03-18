CFLAGS=-std=gnu99
all :command simple_command helper_to_parser lex_config yacc_config main
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
	gcc -g $(CFLAGS) lex.yy.c y.tab.c -Wall main.c simple_command_functions.o command_functions.o helper_to_parser.o -ll -w -o main 
binaries= simple_command command main
clean:
	rm -f $(binaries) *.o