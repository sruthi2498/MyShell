#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "simple_command_functions.h"
#include "command_functions.h"

#define MAX_NUMBER_OF_SIMPLE_COMMANDS 100

 
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

