#include "all_include.h"


int main(){
	StackInit();
	InitCommand();
	command_to_be_pushed=malloc(sizeof(char)*STACK_ELEM_SIZE);
	
	Prompt=malloc(sizeof(char)*PROMPT_SIZE);
	strcpy(Prompt,"hash:~");


	prompt();

	if(!yyparse()){
			//printf("\nParsed Successfully\n");

	} 
	

}