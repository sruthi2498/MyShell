CFLAGS=-std=gnu99
all : command simple_command main
command : command_functions.c command_functions.h all_include.h
	gcc -g $(CFLAGS) -c command_functions.c -o command_functions.o -w
simple_command : simple_command_functions.c simple_command_functions.h all_include.h
	gcc -g $(CFLAGS) -c simple_command_functions.c -o simple_command_functions.o -w
main : main.c all_include.h
	gcc -g $(CFLAGS) -o main -Wall main.c simple_command_functions.o command_functions.o -w
binaries= simple_command command main
clean:
	rm -f $(binaries) *.o