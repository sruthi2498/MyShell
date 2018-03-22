
#Use GNU compiler
cc = gcc -g
CC = g++ -g

all: shell cat_grep ctrl-c 

lex.yy.o: shell.l 
	lex shell.l
	$(cc) -c lex.yy.c

y.tab.o: shell.y
	yacc -d shell.y
	$(CC) -c y.tab.c

command.o: command.cc
	$(CC) -c command.cc

shell: y.tab.o lex.yy.o command.o
	$(CC) -o shell lex.yy.o y.tab.o command.o -ll

cat_grep: cat_grep.cc
	$(CC) -o cat_grep cat_grep.cc

ctrl-c: ctrl-c.cc
	$(CC) -o ctrl-c ctrl-c.cc

clean:
	rm -f lex.yy.c y.tab.c  y.tab.h shell ctrl-c  cat_grep *.o

