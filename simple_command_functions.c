#include "all_include.h"

void InitSimpleCommand(){

	CurrentSimpleCommand._numberOfAvailableArguments=MAX_NUMBER_OF_ARGUMENTS; 
    CurrentSimpleCommand._numberOfArguments=0; 
    
    CurrentSimpleCommand._arguments=malloc(sizeof(char *)*CurrentSimpleCommand._numberOfAvailableArguments);

    //Allocates space for 10 possible arguments
    for(int i=0;i<CurrentSimpleCommand._numberOfAvailableArguments;i++){
    	 CurrentSimpleCommand._arguments[i]=malloc(sizeof(char)*MAX_LEN_OF_ARG);
    }


    //printf("InitSimpleCommand over\n");

}

int insertArgument( char * argument ){

	//printf("Inserting arg %s\n",argument);
	if( CurrentSimpleCommand._numberOfArguments >= CurrentSimpleCommand._numberOfAvailableArguments){
		printf("Max number of arguments reached, insertArgument FAILED\n");
		return 0;
	}

	CurrentSimpleCommand._arguments[CurrentSimpleCommand._numberOfArguments]=argument;
	
	CurrentSimpleCommand._numberOfArguments++;
	//printf("Inserted %s\n",CurrentSimpleCommand._arguments[CurrentSimpleCommand._numberOfArguments]);
	return 1;
}

