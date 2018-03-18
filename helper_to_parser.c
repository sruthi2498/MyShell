#include "all_include.h"

//Initialize a global intermediate array to store arguments
int Init_parsed_args(){
	parsed_arg=malloc(sizeof(char *) * MAX_NUMBER_OF_ARGUMENTS);

	for(int i=0; i<MAX_NUMBER_OF_ARGUMENTS; i++){
		parsed_arg[i] = malloc(sizeof(char) * MAX_LEN_OF_ARG);
	}	
	count_arg = 0;
}

//Send the arguments in reverse order to actual SimpleComand
int Send_all_args(){

	printf("Sending all args \n");
	for(int i=count_arg-1; i>=0; i--){
		insertArgument(parsed_arg[i]);
		
	}	
	insertArgument(NULL);
	return 1;
	//for i = number of args to 0
		//insertArgument(arg_list[i])

	//Append NULL as last argument

}

//Insert each argument into intermediate array (in reverse order)
int Insert_parsed_arg(char *buf){

	printf("Inserting parsed arg %s\n", buf);
	char *temp = strdup(buf);
	parsed_arg[count_arg] = temp;
	count_arg++;

}