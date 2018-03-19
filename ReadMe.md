
ABOUT SHELL PROGRAMMING-

A shell program is an application that allows interacting with the computer. In a shell the user 
can run programs and also redirect the input to come from a file and output to come from a 
file. Shells also provide programming constructions such as if, for, while, functions, variables 
etc. Additionally, shell programs offer features such as line editing, history, file completion, 
wildcards, environment variable expansion, and programing constructions. 


Parts of a Shell Program :-

The shell implementation is divided into three parts: The Parser​, The Executor​, and Shell 
Subsystems.
The Parser
The Parser is the software component that reads the command line such as “ls ­al” and puts it 
into a data structure called Command Table​ that will store the commands that will be 
executed. 
The Executor
The executor will take the command table generated by the parser and for every 
SimpleCommand in the array it will create a new process. 


WorkFlow-:
All files and each function in them -
a) simple_command_functions.c
    -void InitSimpleCommand() :- Initialised the SimpleCommand structure to store arguments
    -int insertArgument( char * argument ) :- Insertion in the argument array of the SimpleCommand structure
b) command_functions.c
    -
