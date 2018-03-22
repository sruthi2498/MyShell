#include "all_include.h"


int main(){

	InitCommand();
	
	Prompt=malloc(sizeof(char)*PROMPT_SIZE);
	strcpy(Prompt,"hash:~");


	prompt();

	if(!yyparse()){
			//printf("\nParsed Successfully\n");

	} 
		//printf("\nParsing Unsuccessful\n");
	// InitCommand();
	// InitSimpleCommand();

	// int ret;

	// ret=insertArgument("ls");
	// ret=insertArgument("-l");
	// ret=insertArgument(NULL);

	// ret=InsertSimpleCommand(CurrentSimpleCommand);

	// InitSimpleCommand();
	// ret=insertArgument("mkdir");
	// ret=insertArgument("test");
	// ret=insertArgument(NULL);

	// ret=InsertSimpleCommand(CurrentSimpleCommand);

	// DisplayCommand();

	// execute();

}