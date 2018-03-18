CFLAGS=-std=gnu99
all : simple_command command 
simple_command : simple_command_functions.c simple_command_functions.h all_include.h
	gcc -g $(CFLAGS) -Wall -c simple_command_functions.c -o simple_command_functions.o -w
command : command_functions.c command_functions.h all_include.h
	gcc -g $(CFLAGS) -Wall -c command_functions.c -o command_functions.o -w
binaries= simple_command command 
clean:
	rm -f $(binaries) *.o