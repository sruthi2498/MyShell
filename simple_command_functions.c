#include "all_include.h"

void InitSimpleCommand(){

	sc++;
	printf("Simple command called %d times\n", sc);
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


	//printf("Inserting arg %s index %d\n",argument,CurrentSimpleCommand._numberOfArguments);


	if( CurrentSimpleCommand._numberOfArguments >= CurrentSimpleCommand._numberOfAvailableArguments){
		printf("Max number of arguments reached, insertArgument FAILED\n");
		return 0;
	}

	CurrentSimpleCommand._arguments[CurrentSimpleCommand._numberOfArguments]=argument;
	//printf("Inserted %s\n",CurrentSimpleCommand._arguments[CurrentSimpleCommand._numberOfArguments]);
	CurrentSimpleCommand._numberOfArguments++;
	
	return 1;
}

