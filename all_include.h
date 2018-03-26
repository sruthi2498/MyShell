#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>


#include "simple_command_functions.h"
#include "command_functions.h"
#include "helper_to_parser.h"
#include "arrow.h"
#include "stack.h"
#include "edit.h"

#define MAX_NUMBER_OF_SIMPLE_COMMANDS 10
#define MAX_NUMBER_OF_ARGUMENTS 10
#define MAX_LEN_OF_ARG 20
#define MAX_CHAR_SIZE_OF_COMMAND 100
#define MAX_CHAR_SIZE_OF_SIMPLECOMMAND 10
#define WRITE_SIZE 250


#define STACK_SIZE 25 //max history allows up to 50 commands
#define STACK_ELEM_SIZE 100 //size of each elem in the stack


#define PROMPT_SIZE 100



int Top;

int HistoryPointer;

struct stack_elem{
        char * command;
        int pid;
        char * time_str;
};

struct stack_elem stack[STACK_SIZE];
 
// Describes a simple command and arguments 
struct SimpleCommand { 
        // Available space for arguments currently preallocated 
        int _numberOfAvailableArguments; 
        // Number of arguments 
        int _numberOfArguments; 
        // Array of arguments 
        char ** _arguments; 

}; 

// Describes a complete command with the multiple pipes if any 
// and input/output redirection if any. 
struct Command { 
        int _numberOfAvailableSimpleCommands;
        int _numberOfSimpleCommands;

        //array of simple commands
        struct SimpleCommand _simpleCommands[MAX_NUMBER_OF_SIMPLE_COMMANDS];

        //variables _outFile, _inputFile, _errFile 
                // ->will be NULL if no redirection was done
                // ->or the name of the file they are being redirected to
        char * _outFile; 
        char * _inputFile; 
        char * _errFile; 

        int _background; 
}; 

struct Command CurrentCommand;
struct SimpleCommand CurrentSimpleCommand;

char** parsed_arg;
char** parsed_final_arg;
int count_arg;

char * Prompt;